#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> PII;

const int N = 100000 + 10;

void merge(vector<PII>& a)
{
    vector<PII> res;
    sort(a.begin(), a.end());//对a进行排序 pair的排序先排左再排右 所以是按区间左端排序

    int st = -2e9, ed = -2e9; //初始化为无穷大

    for(auto seg : a)
        if(ed < seg.first)  //没有重叠
        {
            if(st != -2e9) res.push_back({st,ed}); //且不是第一个元素 将其加入答案
            st = seg.first,ed = seg.second; //这是第一个
        }
        else //有重叠
        {
            ed = max(ed, seg.second);
        }


        if(st != -2e9) res.push_back({st,ed});//加入最后一组  不要遗漏

        a = res;
}


int main()
{
int n;
    scanf("%d", &n);

    vector<PII> segs;
    for (int i = 0; i < n; i ++ )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        segs.push_back({l, r});
    }

    merge(segs);

    cout << segs.size() << endl;

    return 0;
}

//作者：IdealDragon
//链接：https://www.acwing.com/activity/content/code/content/44128/
