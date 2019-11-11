#include <iostream>
const int N = 100010;
using namespace std;

//表示在[l,r]区间上加上c
void insert(int l, int r, int c, int b[])
{
    b[l] += c;
    b[r + 1] -= c;
}
int main()
{
     int n, m;
     scanf("%d %d", &n, &m);
     int a[n + 1] = {0}, b[n + 1] = {0};
     //获得原始数组
     for(int i = 1; i <= n; i++) scanf("%d", &a[i]);//这个a[i]还不是我们假设中的全0的a[i]；
     //一开始假设a[i] b[i]都是0 
     //那么第一次的一轮区间操作就是给每个[i,i]区间加上a[i] 从而得到第一轮操作后的a[i] b[i]
     for(int i = 1; i <= n; i++) insert(i, i, a[i], b);
    while(m--)
    {
        int r, l, c;
        scanf("%d %d %d", &l, &r, &c);
        insert(l, r, c, b);
    }

    for(int i = 1; i <= n; i++)
        {
            b[i] += b[i - 1];
            printf("%d ",b[i]);
        }


    return 0;
}

//作者：IdealDragon
//链接：https://www.acwing.com/activity/content/code/content/41703/
