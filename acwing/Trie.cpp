#include <iostream>

using namespace std;

const int N = 100010;
//son[][26]存储树中每个节点的子节点  cnt[]存储以每个节点结尾的单词数量
//0号节点既是根节点也是空节点,idx是当前访问的是哪个节点
int son[N][26], cnt[N], idx;
char s[N];

void insert(char str[])
{
    int p = 0;
    for(int i = 0; str[i]; i++)
    {
        int u = str[i] - 'a';
        if(!son[p][u]) son[p][u] = ++idx;//如果当前节点的子节点没有要插入的字母，则创建一个节点，并增加idx
        p = son[p][u];//当前节点移到子节点
    }
    cnt[p] ++;//一个节点结束，这个节点处的cnt数组加1
}

int query(char str[])
{
    int p = 0;
    for(int i = 0; str[i]; i++)
    {
        int u = str[i] - 'a';
        if(!son[p][u]) return 0;//数组中不存在则返回0
        p = son[p][u];    //移动到下一个节点
    }
    return cnt[p];
}


int main()
{
    int n = 0;
    scanf("%d",&n);
    char op[2];
    while(n--)
    {
        scanf("%s%s",op,s);
        if(*op == 'I') insert(s);
        else  cout << query(s) << endl;
    }
    return 0;
}

//作者：IdealDragon
//链接：https://www.acwing.com/activity/content/code/content/46598/
