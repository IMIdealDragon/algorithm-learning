#include <iostream>
const int N = 100000 + 10;
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int a[n];
    for(int i = 0; i < n; i++) scanf("%d",&a[i]);
    //计算前缀和
    int s[n];
    s[0] = 0;
    for(int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i - 1];
    while(m--)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        cout << s[r] - s[l - 1] <<endl;      
    }
    return 0;
}