#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
typedef pair<int,int> PII;

const int N = 110;

int map[N][N];
bool st[N][N];
int d[N][N];


int main()
{
    
    queue<PII> q;
    int cnt = 0;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int n,m;

    scanf("%d%d", &n,&m);
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
          scanf("%d",&map[i][j]);
     memset(d, -1, sizeof d);
          
    st[0][0] = true;
    d[0][0] = 0;
    q.push({0,0});
    
     while(q.size())
     {
        PII t = q.front();
        q.pop();
        int x = 0, y = 0;
        for(int i = 0;i < 4; i++)
        {
             x = t.first  + dx[i];
             y = t.second + dy[i];

        
            if (x >= 0 && x < n && y >= 0 && y < m && map[x][y] == 0 && d[x][y] == -1)
            {
                d[x][y] = d[t.first][t.second] + 1;
                q.push({x,y});
                
            }           

        }
        
     }
          
    cout << d[n - 1][m - 1] << endl;
    return 0;
}