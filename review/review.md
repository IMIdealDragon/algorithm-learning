# DFS + 递归问题

[TOC]

## DFS模板

dfs问题最重要的是想清楚一个遍历的顺序，dfs又称为暴搜。想到一个层层dfs的顺序，这个可以认为是二叉树的纵向生长顺序，而每一层都会有for循环，这个就是二叉树同层的不同节点。所以主要是把这个二叉树画出来，然后和代码对应上。

```cpp
void dfs(int u)//u是搜索顺序的那个索引把
{
    //判断终止条件
    st[u] = true;//记录这个点被搜索了
    for(int i = h[u]; i != -1; i = ne[u])
    {
        int j = e[i];
        if(!st[j])  dfs(j);
    }
    st[u] = false;//恢复现场
}
```

## 组合数

### leetode 216

题目描述
给定数字1到9，从中选 kk 个数，不考虑顺序，使得它们的和等于 nn，返回所有方案。要求方案中不包含相同数字，且答案中不包含相同的方案。

样例1
输入：k = 3, n = 7
输出：[[1,2,4]]
样例2
输入：k = 3, n = 9
输出：[[1,2,6], [1,3,5], [2,3,4]]

解法：
这道题是组合数问题，组合数采用DFS的时候，我是需要记录一个起点的，而排列数则是不需要的。

我们的搜索顺序第一层是分别以1~9为起点，然后再进行递归。

```cpp
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> tmp;
    vector<vector<int>> combinationSum3(int k, int n) {
       dfs(k, n, 1);
        return ans;
    }
    
void dfs(int k, int n, int start)
{
    if(!k)
    {
        if(!n) ans.push_back(tmp);
        return ;
    }
    for(int i = start; i <= 10 - k; ++i)
    {
        tmp.push_back(i);
        dfs(k - 1, n - i, i + 1);
        tmp.pop_back();
    }
}
};
```

## 全排列

### 剑指offer38   leetcode46，47

输入一组数字（可能包含重复数字），输出其所有的排列方式。

**样例**

```
输入：[1,2,3]

输出：
      [
        [1,2,3],
        [1,3,2],
        [2,1,3],
        [2,3,1],
        [3,1,2],
        [3,2,1]
      ]
```

```cpp
//第一种是直接利用STL里面的next_permutation就能得到这个不同的排列
// class Solution {
// public:
//     vector<vector<int>> permutation(vector<int>& nums) {
//         vector<vector<int> > ans;
//         sort(nums.begin(),nums.end());
//         do{
//             ans.push_back(nums);
//         }while(next_permutation(nums.begin(), nums.end()));
        
//         return ans;
//     }
// };

//当然是要自己重新实现一遍的，这是leetcode47题，类似的有46题可以对比
//之前还有一道题是没有重复数字的，那样很简单，只要每次递归，放一个位置就可以了
//现在有重复数字，就得考虑重复数字怎么放的问题，这样的话，我们先排序
//然后，假如是11233这样的序列，把对于第二个1我们就只把他放到第一个1的后面，
//用start记录和当前数字相同的上一个位置
class Solution {
public:
    vector<bool> st;
    vector<int> path;
    vector<vector<int>> ans;

    vector<vector<int>> permutation(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        st = vector<bool>(nums.size(), false);
        path = vector<int>(nums.size());
        dfs(nums, 0, 0);
        return ans;
    }

    void dfs(vector<int>& nums, int u, int start)
    {
        if (u == nums.size())
        {
            ans.push_back(path);
            return;
        }

        for (int i = start; i < nums.size(); i ++ )
            if (!st[i])
            {
                st[i] = true;
                path[i] = nums[u];//在第i个位置放nums[u],然后递归，这个第i个数返回不用删除的原因是后面会覆盖
                if (u + 1 < nums.size() && nums[u + 1] != nums[u])
                    dfs(nums, u + 1, 0);
                else
                    dfs(nums, u + 1, i + 1);
                st[i] = false;
            }
    }
};
```

### 字符串解码

给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

示例:

s = "3[a]2[bc]", 返回 "aaabcbc".
s = "3[a2[c]]", 返回 "accaccacc".
s = "2[abc]3[cd]ef", 返回 "abcabccdcdcdef".

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/decode-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

> 根据这道题可以学习下c++里面字符串的处理方法，用iostringstream

```cpp
//这道题的递归顺序好想，但是主要是递归时候的终止和开始的条件需要思考一下
//当然这道题还是用栈的面大一点
//这种做法的iostringtream的使用挺好的
class Solution {
public:
    string decodeString(string s) {
        istringstream iss(s);
        return dfs(iss);
    }
    string dfs(istringstream& iss){
        string res;//这一层的返回值
        char ch;//临时变量
        int k = 0;//当前这个[前的数字
        while(iss >> ch){
            if(ch >= '0' && ch <= '9'){
                k = k * 10 + ch - '0';//计算[之前的数
            }
            else if(ch == '[')//遇到一个[就往下一层
            {
                string tmp = dfs(iss);
                while(k)
                {
                    res += tmp;
                    --k;
                }
            }
            else if(ch == ']')//遇到一个‘]’就返回一层
            {
                return res;
            }
            else     
            {
                res += ch;
            }
        }
        return res;
    }
};
```

## 排序专题

### 堆排序

>  剑指offer40题，leetcode215

在未排序的数组中找到第 k 个最大(其实也可以最小，先按最大看吧)的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

示例 1:

输入: [3,2,1,5,6,4] 和 k = 2
输出: 5
示例 2:

输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/kth-largest-element-in-an-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

**解法1：堆排序**

维护一个大小为k的小顶堆就可以了。

建堆的时间复杂度O(N)  插入删除的时间复杂度O(logN)

本题的时间复杂度 `O(k) + (n-k) * O(logk)` 当k=n/2时，复杂度退化为nlogn

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> q2;//小顶堆
        for(int i = 0; i < k; i++)
            q2.push(nums[i]);
        for(int i = k; i < nums.size(); i++)
            if(nums[i] > q2.top())
            {
                q2.pop();
                q2.push(nums[i]);
            }
        
        return q2.top();
    }
};
```

**解法2**

快排模板：

每次以数组的第一元素取出来作为轴点，然后将比它小的放左边，比它大的放右边

```cpp
void quick_sort(int q[], int l, int r)
{
    if (l >= r) return;
    
    int i = l - 1, j = r + 1, x = q[l];
    while (i < j)
    {
        do i ++ ; while (q[i] < x);
        do j -- ; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
        else break;
    }
    quick_sort(q, l, j), quick_sort(q, j + 1, r);
}
```

基于快排的,时间复杂度分析：平均O(nlogn)，最坏O(n^2)

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int low = 0, high = nums.size() - 1, mid = 0;
       while (low <= high) {
           mid = partation(nums, low, high);//该函数使得mid左边都大于mid，右边都小于mid
           if (mid == k - 1) return nums[mid];
           else if (mid > k - 1) high = mid - 1;
           else low = mid + 1;
       }
       return -1;
   }
   
   int partation(vector<int>& nums, int low, int high) {
       int left = low + 1, right = high;
       swap(nums[low], nums[(low + high) / 2]);//将首元素与中间元素交换，降低最坏情况的概率
       int bound = nums[low];//取nums[low]作为轴点
       while (left <= right) {
           while (left < high && nums[left] >= bound) left++;
           while (nums[right] < bound) right--;
           if (left < right) 
               swap(nums[left++], nums[right--]);
           else break;
       }
       swap(nums[low], nums[right]);
       return right;
   }
};
```

