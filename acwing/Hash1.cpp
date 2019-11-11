//哈希算法分为两种，一种是拉链法，一种是开放寻址法，操作有，插入和查询，删除不常用

//开放寻址法，插入操作是，先计算得到k，如果h[k]位置已经被占，则找下一个位置，直到找到空位置为之
//而查找操作，也是从h[k]，开始查找，一直到找到元素或者空元素为止，如果找到返回找到的位置，如果没有找到返回应该插入的位置

#include <iostream>
#include <cstring>
const int N = 200003, null = 0x3f3f3f3f;//开放寻址法N要比数据量大一些才行，然后null是标志空位置
int h[N];

int find(int x)
{
    int k = (x % N + N) % N;
    while(h[k] != null && h[k] != x)
    {
        k++;
        if(k == N) k = 0;
    }
    
    return k;
}

int main()
{
    int n;
    scanf("%d", &n);
    memset(h, 0x3f, sizeof h);
    int ops[2], m;
    while(n--)
    {
        scanf("%s%d", ops, &m);
        int idx = find(m); 
        if (*ops == 'I') h[find(m)] = m;
        else
        {
            if (h[find(m)] == null) puts("No");
            else puts("Yes");
        }
    }
    
    return 0;
}


/*
//拉链法，维护一个数组，每个元素（槽）拥有一个链表（拉链）

#include <iostream>
#include <cstring>

using namespace std;

const int N = 100003;//大于100000的最小质数，一般取质数能使得哈希冲突最小

int h[N], e[N], ne[N], idx = 0;//h是维护的数组，e[N],和ne[N]维护链表，idx表示链表当前使用的结点

void insert(int x)
{
    int k = (x % N + N) % N;//原来是直接x%N就可以的，但是这里是为了处理负数的情况
    e[idx] = x;//将x存下来，放到e数组当中
    ne[idx] = h[k];//将x的ne指向原来的h[k]，也就是这条链条的头部
    h[k] = idx;//将x的idx存入h[k]中，插入到了头中；
    idx++;
}

bool find(int x)
{
    int k = (x % N + N) % N;
    for(int i = h[k]; i != -1; i = ne[i])
    {
        if(e[i] == x)
            return true;
    }
    
    return false;
}

int main()
{
    int n;
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    
    int ops[2], m;
    for(int i = 0; i < n; i++)
    {
        scanf("%s%d", ops, &m);
        if(*ops == 'I') insert(m);
        else 
        {
            if(find(m)) puts("Yes");
            else puts("No");
        }
    }
    
    return 0;
}
*/