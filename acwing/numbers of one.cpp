#include <iostream>

using namespace std;
int count(int x)
{
    int k = 0, cnt = 0;
    do
    {
       if( x & 1) cnt++; 
        x = x >> 1;
    }while(x);

    return cnt;
}

int main()
{
    int n = 0;
    cin >> n;
    int a[n], b[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%d",&a[i]);
        a[i] = count(a[i]);
        cout << a[i] << " " ;
    }
    cout << endl;

    return 0;
}

//作者：IdealDragon
//链接：https://www.acwing.com/activity/content/code/content/44008/
