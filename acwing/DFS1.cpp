//1~n全排列
//dfs深搜，几个问题：返回条件：到达叶节点
//保存现场：在进入下一层前后，需要将一些相关变量做一下保存
//回溯：返回以后做一个回溯
#include <iostream>

const int N = 10;
using namespace std;

int path[N];//保存找到的某种全排列方案 path[i]表示第i个位置存的数
bool st[N]; //保存状态
int n;

void dfs(int u)
{
    //写递归之前先写返回条件，深搜就是到达叶节点
    if(u == n)
    {
        for(int i = 0; i < n; i++)
             printf("%d ", path[i]);
        printf("\n");
    }
    
    for(int i = 1; i <= n; i++)
    {
        if(!st[i])
        {
            path[u] = i;
            st[i] = true;
            dfs(u + 1);
            st[i] = false;
        }
    }
}
int main()
{
    scanf("%d", &n);
    
    dfs(0);
    
    return 0;
}