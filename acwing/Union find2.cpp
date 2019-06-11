#include <iostream>
#include <string>
using namespace std;
const int N = 100010;
int p[N], size[N];

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        p[i] = i;
        size[i] = 1;
    }
    string ops;
    int a, b, aa, bb;
    while(m--)
    {
        cin >> ops;
        if(ops == "C")
        {
            scanf("%d%d", &a, &b);
            aa = find(a), bb = find(b);
            if(aa != bb)
            {
                p[aa] = bb;//a归入到b
                size[bb] += size[aa];
            }
        }
        else if(ops == "Q1")
        {
            scanf("%d%d", &a, &b);
            aa = find(a), bb = find(b);
            if(aa == bb) puts("Yes");
            else puts("No");
        }
        else
        {
            scanf("%d", &a);
            aa = find(a);
            cout << size[aa] << endl;
        }
            
        
    }
    
    return 0;
}

//链接：https://www.acwing.com/problem/content/839/