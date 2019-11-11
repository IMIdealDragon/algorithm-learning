/*KMP算法 是相当经典 这里分为两步，第一步是求P字符串的next数组
 *第二步是进行匹配，如果未能成功匹配，则j = next[j] 跳转至next数组进行处理
 *P数组的next数组存的是，next[i] = j 表示 p[1~j] = p[i-j+1,i]，
 *且这是前缀与后缀能匹配的最大长度
 */
 #include <iostream>
 using namespace std;
 const int N = 1e4 + 10, M = 1e5 + 10;
 char  p[N], s[M];
 int ne[N];
 int main()
 {
     int n = 0, m = 0;
     
     scanf("%d\n",&n);
     for(int i = 1; i <= n; i++)
     scanf("%c",&p[i]);
     
     scanf("%d\n",&m);
     for(int i = 1; i <= m; i++)
     scanf("%c",&s[i]);
     
     //先求next数组

     for(int i = 2, j = 0; i <= n; i++)
     {
         while(j && p[i] != p[j + 1]) j = ne[j];//如果不匹配 就将p右移 也就是j指针退回去
         if(p[i] == p[j + 1]) j++;//如果能匹配那就是接着下一个
         ne[i] = j;//将此时的j记录给next
     }
     
//匹配
      for (int i = 1, j = 0; i <= m; i ++ )
    {
        while (j && s[i] != p[j + 1]) j = ne[j];
        if (s[i] == p[j + 1]) j ++ ;
        if (j == n)//如果j匹配到了下一个 说明p已经完全匹配  可以实现逻辑
        {
            printf("%d ", i - n);
            j = ne[j];
        }
    }
     
     return 0;
 }