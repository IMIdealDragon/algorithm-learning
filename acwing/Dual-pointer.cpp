/*
 *双指针算法能够效率高的原因是因为跟暴力搜索相比，省去了j在i前面的组合情况
 *一直都是i在前，j在后，i负责遍历，j负责后期check配合。
 */

#include <iostream>
#include <unordered_map>

const int N = 100000 + 10;

using namespace std;
int main()
{
    int n;
    cin >> n;
    int a[n];
    unordered_map<int, int> s;
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    int res = 0;
    //双指针算法，i在前面，作为负责的节点，j在后面跟随，满足条件才前进
    for(int i = 0, j = 0; i < n; i++)
    {
        s[a[i]]++;
        while(j < i && s[a[i]] > 1) s[a[j++]]--; //如果此时有重复数字了 应该将j与i之间的数都去掉，相应的计数有需要挨个去掉
        //否则，具体问题的逻辑，此题是计算i j 夹的元素数目
        res = max(res, i - j + 1);
    }

    cout << res << endl;

    return 0;
}

//作者：IdealDragon
//链接：https://www.acwing.com/activity/content/code/content/43616/
