//当前是权重都为1，所以最短路问题可以用BFS来解决，
//就是按层搜索，往往需要找一个数组记录每一个元素是处于搜索的第几层
//需要一个队列来保存依次访问的元素
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int const N = 100010;

int h[N], e[2 * N], ne[2 * N], idx;
int d[N];
queue<int> q;

void insert(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    
    int a, b;
    for(int i = 0; i < m; i++)
    {
        scanf("%d%d", &a, &b);
        insert(a, b);
        
    }
    
    memset(d, -1, sizeof d);
    d[1] = 0;
    q.push(1);
    while(q.size())
    {
        int t = q.front();
        q.pop();
        
        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];//把元素取出来
            if(d[j] == -1)
            {
                d[j] = d[t] + 1;
                q.push(j);
            }
        }
    }
    
    cout << d[n] << endl;
    
    return 0;
}