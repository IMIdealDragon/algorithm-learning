#include <iostream>

const int N = 100000 + 10;
using namespace std;


void quick_sort(int q[], int l, int r)
{
    if(l >= r) return ;
    int i = l - 1, j = r + 1, x = q[l];
    while(i < j)
    {
        while(q[++i] < x);
        while(q[--j] > x);
        if(i < j) swap(q[i], q[j]);
        else break;
    }

    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}
int main()
{
    int n = 0, k = 0;
    scanf("%d %d", &n, &k);
    if(k > n) return -1;
    int q[n];    
    for(int i = 0; i < n; i++) scanf("%d",&q[i]);

    quick_sort(q, 0, n - 1);

    printf("%d",q[k - 1]);

    return 0;
}

//作者：IdealDragon
//链接：https://www.acwing.com/activity/content/code/content/41011/
