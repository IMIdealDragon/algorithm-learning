/*关于两个二分模板的话 就是如果只是判断能不能有匹配 两个都可以用
 *然后写mid的时候先可以不加1 然后看后面的区间选取 如果用到mid + 1前面mid除以2的时候就不加1
 *用到mid - 1前面就得加1
 */

#include <iostream>
const int  N = 100000 + 10;

int main()
{
    int n = 0, q = 0;
    scanf("%d %d",&n, &q);
    int a[n];
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    int m = 0;
    while(q--)
    {
        scanf("%d",&m); //读取要查询的数
        //求匹配数下界的二分
        int l = 0, r = n - 1;
        while(l < r)    //第一次二分寻找最左边的匹配 mid向下取整 
        {
            int mid = r + l >> 1;
            //另外这里是check满足条件的 所以取区间的时候要r=mid 把mid归进去。
            if(a[mid] >= m) r = mid; //这个时候应该是往小的区间去寻找 即便相等也要再次缩小区间
            else l = mid + 1;//不满足check条件可以直接放弃mid了
        }
        if(a[l] != m) printf("%d %d\n", -1, -1); //如果没有匹配直接输出-1 -1
        else
        {
            printf("%d ",l);
            //求匹配数的上界的二分
            l = 0, r = n - 1;
            while(l < r)
            {
                int mid = r + l + 1>> 1;//mid向上取整 寻找最右边的匹配
                if(a[mid] <= m) l = mid;
                else r = mid - 1;
            }
            printf("%d\n",r);
        }
    }
    
    return 0;
}