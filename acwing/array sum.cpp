#include <iostream>

using namespace std;

const int N = 100000 + 10;

int main()
{
    int n, m, x;
    cin >> n >> m >> x;

    int a[n],b[m];

    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for(int j = 0; j < m; j++)
        scanf("%d", &b[j]);

//这里的双指针选取要一个从低点一个从高点        
    for(int i = 0, j = m - 1; i < n; i++)
    {
        while(j > 0 && a[i] + b[j] > x) j--;
        if(j >= 0 && a[i] + b[j] == x) cout << i <<" "<< j << endl;

    }

    return 0;
}

//作者：IdealDragon
//链接：https://www.acwing.com/activity/content/code/content/43631/
