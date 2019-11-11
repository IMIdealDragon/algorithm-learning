//删除某个节点以后，连通块一共分为几个部分：除去当前的节点及其子树为一个部分，这部分的节点数就是总数减去该树
//还有一部分是该节点的各个子节点形成的子数。
//第一步：先要表示出该图，是无向图，每次都需要建立双向的连接
//第二步：用dfs求出每个节点所包含的节点数

#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010;

//表示图需要一个数组加一组链表，用数组模拟
int h[N], e[2 * N], ne[2 * N], idx;
bool st[N];
int ans = N;
int n;

//模拟链表，从头结点插入b,h[a]中存放链表头结点的idx，ne[idx]中就是存放e[idx]指向的下一个节点idx
//步骤：先存下b，然后把h[a]放入ne存为下一个节点（改变next指针），然后把h[a]指向idx(头结点指向新元素),idx++;
void insert(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];//当前的h[a]成为当前的e[idx]的下一个节点
    h[a] = idx++;
}

//返回的是以u为根的子树的大小
int dfs(int u)
{
    st[u] = true;//标记一下已经遍历过了
    int sum = 1, res = 0; //sum表示当前子树的大小，res表示删除该节点后每个子连通块的大小
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];//搜链表
        if(!st[j])
        {
            int s = dfs(j);//返回j子树的节点数大小
            
            res = max(res, s);//取最大值
            sum += s;//该条链表上的所有子树的节点数加起来
        }
    }
    
    res = max(res, n - sum);//上方的树减去该节点的树
    ans = min(ans, res);
    
    return sum;
     
}
int main()
{
    
    cin >> n;
    memset(h, -1, sizeof h);
    
    int a, b;
    for(int i = 0; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        insert(a,b);
        insert(b,a);
    }
    dfs(1);
    
    cout << ans << endl;
    return 0;
}