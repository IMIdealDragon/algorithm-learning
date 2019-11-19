# 算法题

[TOC]

## DFS问题

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

### 组合数

#### leetode 216

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

### 全排列

#### 剑指offer38   leetcode46，47

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

## 二叉树

### 重建二叉树

输入一棵二叉树前序遍历和中序遍历的结果，请重建该二叉树。

**注意**:

- 二叉树中每个节点的值都互不相同；
- 输入的前序遍历和中序遍历一定合法；

**样例**

```
给定：
前序遍历是：[3, 9, 20, 15, 7]
中序遍历是：[9, 3, 15, 20, 7]

返回：[3, 9, 20, null, null, 15, 7, null, null, null, null]
返回的二叉树如下所示：
    3
   / \
  9  20
    /  \
   15   7
```

[题解]: 
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //前序遍历是根->左->右  中序遍历是：左->中->右
 //所以，布局对于前序遍历就是：[根][左][右] 中序是[左][根][右]
 //所以，我们可以构造先根据根节点的位置去构造子树，从前序找到根，到中序找到相同节点的位置
// 每次递归需要把pre和vin中的位置都传进去
class Solution {
public:
    unordered_map<int, int> pos;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        for(int i = 0; i < inorder.size(); i++)
            pos[inorder[i]] = i;
    
        return dfs(preorder, inorder, 0, n - 1, 0, n - 1);
        
    }
    
    TreeNode* dfs(vector<int>& preorder, vector<int>& inorder,int pl, int pr, int il, int ir)
    {
        if(pl > pr) return NULL;//终止条件
        //找到根节点
        TreeNode *root = new TreeNode(preorder[pl]);
        int k = pos[preorder[pl]] - il;//找到左子数的数量
        root->left = dfs(preorder, inorder, pl + 1, pl + k, il, il + k - 1);
        root->right = dfs(preorder, inorder, pl + k + 1, pr, il + k + 1, ir);
        
        return root;
    }
    
};
```

###  二叉树的下一个节点

给定一棵二叉树的其中一个节点，请找出中序遍历序列的下一个节点。

**注意：**

- 如果给定的节点是中序遍历序列的最后一个，则返回空节点;
- 二叉树一定不为空，且给定的节点一定不是空节点；

**样例**

```
假定二叉树是：[2, 1, 3, null, null, null, null]， 给出的是值等于2的节点。

则应返回值等于3的节点。

解释：该二叉树的结构如下，2的后继节点是3。
  2
 / \
1   3
```

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode *father;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL), father(NULL) {}
 * };
 */
 //主要是分清楚什么是二叉树的后继节点
 //二叉树后继节点，中序遍历的后一个节点
//（1）有右子树，右子树的最左节点是后继
//（2）无右子树，并且是父节点的左孩子，父节点为后继
//（3）无右子树，并且是父节点的右孩子，查该节点是哪个节点左子树的最后节点
//（一直往上找，找到一个节点是父节点的左孩子，则该父节点为后继节点）
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* p) {
        if(p->right)
        {
            p = p->right;
            while(p->left) p = p->left;
            return p;
        }
		//两步写到一起就行，如果当前树不是祖先的左子树（就是右子树）就一直往上
        while(p->father && p == p->father->right) p = p->father;
        return p->father;
    }
};
```

###  树的子结构

输入两棵二叉树A，B，判断B是不是A的子结构。

我们规定空树不是任何树的子结构。

**样例**

树A：

```
     8
    / \
   8   7
  / \
 9   2
    / \
   4   7
```

树B：

```
   8
  / \
 9   2
```

返回 **true** ,因为B是A的子结构。

```cpp
 //将A树每个节点为根节点的子树与B树做匹配
 //单独设计一个匹配函数
class Solution {
public:
    bool isSame(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        //B树没有节点了，则真
        if(!pRoot2) return true;
        //A没节点了或者不相等
        if(!pRoot1 || pRoot1->val != pRoot2->val) return false;
        return isSame(pRoot1->left, pRoot2->left) && isSame(pRoot1->right, pRoot2->right);
    }
    bool hasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        if(pRoot1 == NULL || pRoot2 == NULL)
            return false;
        if(isSame(pRoot1,pRoot2)) return true;
        return hasSubtree(pRoot1->left, pRoot2) || hasSubtree(pRoot1->right, pRoot2);
    }
};
```

###  二叉树的镜像

输入一个二叉树，将它变换为它的镜像。

**这道题的方法是将每个节点的左右子树都交换一下，最后就能形成整颗子树的镜像**

**样例**

```
输入树：
      8
     / \
    6  10
   / \ / \
  5  7 9 11

 [8,6,10,5,7,9,11,null,null,null,null,null,null,null,null] 
输出树：
      8
     / \
    10  6
   / \ / \
  11 9 7  5

 [8,10,6,11,9,7,5,null,null,null,null,null,null,null,null]
```

```cpp
 //把每个节点的左右子节点互换
class Solution {
public:
    void mirror(TreeNode* root) {
        if(!root) return;
        swap(root->left, root->right);
        mirror(root->left);
        mirror(root->right);
    }
};
```

### 对称的二叉树

请实现一个函数，用来判断一棵二叉树是不是对称的。

如果一棵二叉树和它的镜像一样，那么它是对称的。

**样例**

```
如下图所示二叉树[1,2,2,3,4,4,3,null,null,null,null,null,null,null,null]为对称二叉树：
    1
   / \
  2   2
 / \ / \
3  4 4  3

如下图所示二叉树[1,2,2,null,4,4,3,null,null,null,null,null,null]不是对称二叉树：
    1
   / \
  2   2
   \ / \
   4 4  3
```

```cpp
 //两个子树互为镜像的条件：
 //1.根节点相同
 //2.A左子树和B右子树互为镜像，且A右子树和B左子树互为镜像
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return !root || dfs(root->left, root->right);
    }
    
    bool dfs(TreeNode* root1, TreeNode* root2)
    {
        if(!root1 || !root2) return !root1 && !root2;//如果其中一个为空，则看是不是同时为空
        
        return root1->val == root2->val && dfs(root1->left, root2->right) && dfs(root1->right, root2->left);
    }
};
```

### 不分行从上往下打印二叉树

从上往下打印出二叉树的每个结点，同一层的结点按照从左到右的顺序打印。

**样例**

```
输入如下图所示二叉树[8, 12, 2, null, null, 6, null, 4, null, null, null]
    8
   / \
  12  2
     /
    6
   /
  4

输出：[8, 12, 2, 6, 4]
```

------

```cpp
//层次遍历 不分行 采用BFS
class Solution {
public:
    vector<int> printFromTopToBottom(TreeNode* root) {
        if(root == NULL) return {};
        vector<int> ans;
        queue<TreeNode *> q;
        q.push(root);
        while(!q.empty())
        {
            auto t = q.front();
            q.pop();
            ans.push_back(t->val);
            if(t->left) q.push(t->left);
            if(t->right) q.push(t->right);
        }

        return ans;
    }
};
```

```cpp
//分行
class Solution {
public:
    vector<vector<int>> printFromTopToBottom(TreeNode* root) {
        if(root == NULL) return {};
        vector<vector<int> > ans;
        queue<TreeNode*> q;
        vector<int> tmp;
        q.push(root);
        q.push(NULL);//以NULL作为分层的标志
        while(q.size())
        {
            auto t = q.front();
            q.pop();
            if(t == NULL)
            {
                if(q.size()) q.push(NULL);//这一步注意判断q是否为空
                ans.push_back(tmp);
                tmp.clear();
                continue;
            }
            tmp.push_back(t->val);
            if(t->left) q.push(t->left);
            if(t->right) q.push(t->right);
        }

        return ans;
    }
};
```

### 二叉搜索树的后序遍历序列

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。

如果是则返回true，否则返回false。

假设输入的数组的任意两个数字都互不相同。

**样例**

```
输入：[4, 8, 6, 12, 16, 14, 10]

输出：true
```

```cpp
//这种题目一般都是去递归重构二叉树，看在重构过程中，会不会出现不符合条件的项
//二叉搜索树的特点：左 < 根 < 右
//后序遍历的顺序是：左 - 右 - 根
//所以根是序列的最后一项，序列中全小于根的区间为根的右子树，全大于根的区间为根的左子树
//如果无法划分出这样的两个区间，则无法重构二叉搜索树
class Solution {
public:
    bool verifySequenceOfBST(vector<int> sequence) {
        if(sequence.empty()) return true;

        return dfs(0, sequence.size() - 1, sequence);
    }

    bool dfs(int l, int r, vector<int>& seq)
    {
        if(l >= r) return true;
        int root = seq[r];//取得该区间的根节点
        int k = l;
        while(k < r && seq[k] < root) k++;//找到全小于当前root的区间
        for(int i = k; i < r; i++)
            if(seq[i] < root)
                return false;//如果说后半区间有小于root的值，说明不构成搜索二叉树
        return dfs(l, k - 1, seq) && dfs(k, r - 1, seq);

    }
};
```

###  二叉树中和为某一值的路径

输入一棵二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。

从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。

**样例**

```
给出二叉树如下所示，并给出num=22。
      5
     / \
    4   6
   /   / \
  12  13  6
 /  \    / \
9    1  5   1

输出：[[5,4,12,1],[5,6,6,5]]
```

```cpp
class Solution {
public:
    vector<vector<int>> ans;
    int cur;
    vector<int> tmp;
    vector<vector<int>> findPath(TreeNode* root, int sum) {
        dfs(root, sum);
        return ans;
    }
    
    void dfs(TreeNode* root, int sum)
    {
        if(root == NULL) return ;
        cur += root->val;
        tmp.push_back(root->val);
        if(!root->left && !root->right && cur == sum) ans.push_back(tmp);
        if(root->left) dfs(root->left, sum);
        if(root->right) dfs(root->right, sum);
        cur -= root->val;
        tmp.pop_back(); //返回处理要放在最后
    }
};
```

### 序列化与反序列化二叉树

请实现两个函数，分别用来序列化和反序列化二叉树。

您需要确保二叉树可以序列化为字符串，并且可以将此字符串反序列化为原始树结构。

**样例**

```
你可以序列化如下的二叉树
    8
   / \
  12  2
     / \
    6   4

为："[8, 12, 2, null, null, 6, 4, null, null, null, null]"
```

**注意**:

- 以上的格式是AcWing序列化二叉树的方式，你不必一定按照此格式，所以可以设计出一些新的构造方式。

```cpp
class Solution {
public:
    void dfs(TreeNode *root, string& ans)
    {
        if(root == NULL)
            ans += "#!";
        else
        {
            ans += to_string(root->val) + "!";
            dfs(root->left, ans);
            dfs(root->right, ans);
        }
    }
    char* Serialize(TreeNode *root) {    
        string ans;
        dfs(root, ans); 
       // char* ret = const_cast<char*>(ans.c_str());这句代码错误，不能这么写
        char *ret = new char[ans.length() + 1];
        strcpy(ret, const_cast<char*>(ans.c_str()));
        return ret;
    }
    TreeNode* Deserialize(char *str) {
        string s(str);
        int u = 0;
        return dfsd(u, s);
    }
    
    TreeNode* dfsd(int& u, string& data)
    {
       if(u == data.size()) return NULL;
        int k = u ;
        while(data[k] != '!') k++;
        if (data[u] == '#') {
            u = k + 1;
            return NULL;
        }
        int sum = 0;
        bool flag = true;
        //如果是有数字的话，取出这个数字
        if(data[u] == '-') {flag = false; u++;}//处理一下负号
        for (int i = u; i < k; i ++) {
            sum = sum * 10 + data[i] - '0';
        }

        if(flag == false) sum = -sum;
        u = k + 1;
        auto root = new TreeNode(sum);
        root->left = dfsd(u, data);
        root->right = dfsd(u, data);
        return root;
    }
};
```

### 二叉搜索树的第k个结点

给定一棵二叉搜索树，请找出其中的第k小的结点。

你可以假设树和k都存在，并且1≤k≤树的总结点数。

样例

```
输入：root = [2, 1, 3, null, null, null, null] ，k = 3

    2
   / \
  1   3

输出：3
```

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *ans;
    void dfs(TreeNode* root, int& k)
    {
        if(!root) return;//如果遍历到空节点
        if(root->left) dfs(root->left, k);//先搜左子树
        k--;
        if(k == 0)
            ans = root;        
        if(k >= 0 && root->right) dfs(root->right, k);
    }
    TreeNode* kthNode(TreeNode* root, int k) {
        dfs(root, k);
        return ans;
    }
};
```

### 二叉树的深度

输入一棵二叉树的根结点，求该树的深度。

从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。

样例

```
输入：二叉树[8, 12, 2, null, null, 6, 4, null, null, null, null]如下图所示：
    8
   / \
  12  2
     / \
    6   4

输出：3
```

```cpp
class Solution {
public:
    int treeDepth(TreeNode* root) {
        if(!root) return 0;       
        return max(treeDepth(root->left), treeDepth(root->right)) + 1; 
    }
};
```

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。

要求不能创建任何新的结点，只能调整树中结点指针的指向。

**注意**：

- 需要返回双向链表最左侧的节点。

例如，输入下图中左边的二叉搜索树，则输出右边的排序双向链表。

![19_23bee494f5-QQ截图20181202052830](D:\A_目标！！！\algorithm\algorithm-learning\review\pic\19_23bee494f5-QQ截图20181202052830.png)

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //把二叉树分为三部分 分别是左子树B，根A，右子树C
 //让B<-A->C
 //我们每次递归返回左子树的最左和最右一对pair
class Solution {
public:
    TreeNode* convert(TreeNode* root) {
        if(!root) return NULL;
        auto sides = dfs(root);
        return sides.first;
    }
    
    pair<TreeNode *,TreeNode *> dfs(TreeNode* root)
    {
        if(!root->left && !root->right) return {root, root};
        if(root->left && root->right)
        {
            auto lsides = dfs(root->left), rsides = dfs(root->right);
            lsides.second->right = root, rsides.first->left = root;
            root->left = lsides.second, root->right = rsides.first;
            return {lsides.first, rsides.second};
        }
        if(root->left)
        {
            auto lsides = dfs(root->left);
            lsides.second->right = root;
            root->left = lsides.second;
            return {lsides.first, root};
        }
        if(root->right)
        {
            auto rsides = dfs(root->right);
            rsides.first->left = root;
            root->right = rsides.first;
            return {root, rsides.second};
        }
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

## 二分法

首先要观察题目是不是查找的题目，查找的题目就有可能用二分，二分的话还要求数组有序。一般都是有序数组才用二分。

二分可能出错的地方：区间为空，答案不存在，有重复元素，开闭的上下界。。

第一步是选择mid，mid选择的时候，有两种，一种是较小的中位数 ` l+(l + r) / 2`一种是较大的中位数`l+(l+r+1) / 2`

第二步是考虑这个判断条件（这个根据具体的题目要好好考虑），主要是要将区间往目标方向收缩

第三步，是根据条件，选择左右区间收缩，这个时候，如果是r=mid,则修正第一步中的中位数，要取较小值，不然的话，只有两个值的时候，一直是r=mid，一直循环，无法让l=r。同理，r = mid -  1的时候，要用较大中位数。

先给出最经典的模板题

### 二分模板题

找一个有序数组中的匹配值，分别找出最左位置和最右位置

```cpp
#include <iostream>
#include <vector>

using namespace std;

//要找target最左的位置，则当取得target等号的时候，我的区间应该是往右走，且是包含这个值
//所以是r=mid，为了防止死循环，mid取较小中位数
int bsearchl(vector<int>& nums, int target)
{
    int l = 0, r = nums.size() - 1;
    while(l < r)
    {
        int mid = l + (r - l )/2;//取中位数偏大
        if(nums[mid] >= target) r = mid;//如果只有两个，r=mid就死循环
        else
            l = mid + 1;
    }
    return l;
}

int bsearchr(vector<int>& nums, int target)
{
    int l = 0, r = nums.size() - 1;
    while(l < r)
    {
        int mid = l + (r - l + 1) / 2;
        if(nums[mid] > target) r = mid - 1;
        else
            l = mid;
    }
    return l;
}
int main()
{
    vector<int> t = {1,2,3,4,4,4,5,6,7,8};
    int al = bsearchl(t,4);
    cout << al << endl;
    int ar = bsearchr(t,4);
    cout << ar << endl;
    return 0;
}
```

### 等比数列求缺失项，有一个等比数列，其中缺失了一项这项不是首尾，请求出这一项，要求O（logN）

这道题是采用二分查找的方式，判断的方法是拿l，r，mid去做比值，看谁的比值比较大，缺失项一定是在大的那个区间，如果是相等的，那一定就是在数量少的那一侧，因为当偶数的时候，数量会不平衡。

这道题因为目标值时缺项，所以l和r中间夹起来比较好，不然容易丢失

```cpp
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int getMissingNumber(vector<int>& nums)
{
	if (nums.empty())
		return 0;
	int l = 0, r = nums.size() - 1;
	if (nums[l] == nums[r]) return nums[l];
	while (l < r - 1)
	{
		int mid = l + (r - l) / 2;//取左边的中位数
		//现在是左边的数量少，如果左右的比值相同，左边有缺项
 		if (nums[mid] / nums[l] >= nums[r] / nums[mid])
			r = mid;//相等的点
		else
			l = mid;
	}
	return sqrt(nums[l] * nums[r]);
};


int main()
{
	vector<int> test = { 1,2};

	int ans1 = getMissingNumber(test);
	cout << ans1 << endl;

	return 0;
}
```

