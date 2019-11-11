#include <iostream>

const int N = 100010;

int q[N];

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

//作者：IdealDragon
//链接：https://www.acwing.com/activity/content/code/content/41008/
