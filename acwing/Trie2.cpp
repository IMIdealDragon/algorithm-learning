/*一共有i个数 如果暴力做法的话就是每两个都得异或一下，时间复杂度是n^2
 *现在考虑遍历外层还是不变，内层循环改成用trie树来实现
 *每遍历到一个x，就是先把x插入到trie树，然后在trie树里面找最大的异或对
 *插入是常规操作，查找的时候，要找和当前x中的位相反的方向的数
 */

 #include <iostream>
 using namespace std;
 const int N = 100010, M = 31 * N;
 int son[M][2], idx, a[N];

 void insert(int x)
 {
     int p = 0;
     for(int i = 30; i >= 0; i--)
     {
         int u = x >> i & 1;//挨个取位
         if(!son[p][u]) son[p][u] = ++idx;
         p = son[p][u];
     }
 }

 int search(int x)
 {
     int t = 0;
     int p = 0;
     for(int i = 30; i >= 0; i--)
     {
        int u = x >> i & 1;
         if(son[p][!u]) 
         {
             p = son[p][!u];//如果和这个位不一样的选择存在，则沿这条路走下去
             t = t * 2 + !u;//并计算当前的值，每移动一位要乘以2
         }
         else
         {
             p = son[p][u];//如果没有这个位相反的，那相同也得走下去啊
             t = t * 2 + u;
         }
     }

     return t;
 }
 int main()
 {
     int n = 0, res = 0;
     scanf("%d", &n);
     for(int i = 0; i < n; i++)
     {
         scanf("%d", &a[i]);
         insert(a[i]); //将输入的数插入到trie树中
     }

     for(int i = 0; i < n; i++) 
     {
         int t = search(a[i]);
         res = max(res, a[i] ^ t);
     }

     cout << res <<endl;

     return 0;
 }


//作者：IdealDragon
//链接：https://www.acwing.com/activity/content/code/content/46693/