#include <iostream>
using namespace std;
const int N = 100010;
int p[N];
//返回x的根节点
int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);

    return p[x];
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) p[i] = i;
    char ops[2];
    int a, b;
    for(int i = 0; i < m; i++)
    {
        scanf("%s%d%d",ops, &a, &b);
        if(*ops == 'M') p[find(a)] = find(b);//a组服从于b组
        else
        {
            if (find(a) == find(b)) puts("Yes");
            else puts("No");
        }

    }
    return 0;
}

//作者：IdealDragon
//链接：https://www.acwing.com/activity/content/code/content/46803/
