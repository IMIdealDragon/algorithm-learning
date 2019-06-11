/*
 *离散化：就是值域比较大的数据 将其有序的映射到从1开始的域内，相当于按大小排名
 *这样操作的时候就直接操作它的名次，通过名次找到具体的值就可以了
 *这道题目里面值域较大的是无限长的坐标值，坐标是无限大的(10^-9 ~ 10^9)
 *因此在对坐标值进行加c操作或者说区间加减操作时，需要先对其进行离散化
 *其方法就是先把所有出现的坐标值放到alls数组，然后排序 去重
 *这里一共的坐标值有n+2m  n的加c操作  m的区间加减操作
 */

#include <iostream>
#include <vector>
#include <algorithm>

 using namespace std;
typedef pair<int, int> PII;
const int N = 300010;

int a[N], s[N];//存储插入的值和前缀和  不放到全局变量大数据ac不过

 int find(int x,const vector<int>& a)
 {
     int l = 0, r = a.size() - 1;
     while(l < r) //找到匹配的里面最小的
     {
        int mid = l + r >> 1;
        if(a[mid] >= x) r = mid;
        else l = mid + 1;
     }

     return r + 1;
 }

 int main()
 {
     int n,m;
     cin >> n >> m; 
     vector<PII> add,query;//从stdin中读入单值加c操作，暂时保存一下
     vector<int> alls;//待离散化的数据

     for(int i = 0; i < n; i++)
     {
         int x = 0, c = 0;
         cin >> x >> c;
         add.push_back({x,c});//暂存
         alls.push_back(x);   //x是待离散化的值
     }

     for(int i = 0; i < m; i++)
     {
         int l = 0, r = 0;
         cin >> l >> r;
         query.push_back({l,r});//暂时保存
         alls.push_back(l);
         alls.push_back(r);
     }

     //排序
     sort(alls.begin(), alls.end());
     //去重
     alls.erase(unique(alls.begin(),alls.end()),alls.end());

     //一顿预处理操作猛如虎 终于开始进入正题了 先处理加c操作
     for(auto item : add)
     {
         int x = find(item.first, alls);//返回item.first在alls数组中的位置
         a[x] += item.second;
     }

     //求前缀和
     for(int i = 1; i <= alls.size(); i++)
     {
         s[i] = s[i - 1] + a[i] ;
     }

     //处理查询
     for(item : query)
     {
         int l = find(item.first,  alls);
         int r = find(item.second, alls);
         cout << s[r] - s[l -1] << endl;
     }


     return 0;
 }

//作者：IdealDragon
//链接：https://www.acwing.com/activity/content/code/content/44054/
