#include <iostream>

using namespace std;

const int N = 1010;
int a[N][N],b[N][N];

void insert(int x1, int y1, int x2, int y2, int c)
{
    b[x1][y1] += c;
    b[x2 + 1][y1] -= c;
    b[x1][y2 + 1] -= c;
    b[x2 + 1][y2 + 1] += c;
}

int main()
{
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    //原始数组
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        scanf("%d", &a[i][j]);
    //通过第一轮操作 得到差分数组
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
              insert(i, j, i, j, a[i][j]);

    //处理查询
    while (q -- )
    {
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        insert(x1, y1, x2, y2, c);
    }

    //求前缀和 得到最终的数组
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
        b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
        printf("%d ",b[i][j]);
        }
        printf("\n");
    }
    return 0;
}

//作者：IdealDragon
//链接：https://www.acwing.com/activity/content/code/content/41891/
