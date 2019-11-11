/*字符串哈希
 *把字符串看成是一个P进制数，P的经验值是131或13331，取这两个值的冲突概率低
 *把P进制数计算转换成十进制数，然后再对Q取模，这样就映射到了0~Q-1的区间，Q的经验值取2^64
 *而因为我们这里用的数据类型是unsigned long long正好是2^64，因此，如果超过会自动溢出，就省了取模的一步
 *h[k]存储字符串中前k个字符串的哈希值，p[k]存储 p^k mod 2^64
 */
#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;

const int N = 100010, P = 131;

int n, m;
char str[N];
ULL h[N], p[N];

//计算[l,r]区间字符串的哈希值
/*
 *hash[1]=s1 
 *hash[2]=s1∗p+s2*p2
 *hash[3]=s1∗p2+s2∗p+s3
 *hash[4]=s1∗p3+s2∗p2+s3∗p+s4
 *hash[5]=s1∗p4+s2∗p3+s3∗p2+s4∗p+s5
 *观察，假如要得到[3,4]的字符串哈希，只要hash[4]-hash[2]*p^(4-2)
 *由此得到[r,l]区间子字符串的哈希值为h[r]-h[l-1]*p^(r-l+1)
 */
ULL get(int l, int r)
{
    return h[r] -h[l - 1] * p[r - l + 1];
}
int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", str + 1);
    p[0] = 1;
    
    for(int i = 1; i <= n; i++)
    {
        h[i] = h[i - 1] * P + str[i];  //本来应该还有一个取模运算
        p[i] = p[i - 1] * P;
    }
    
    while(m--)
    {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if (get(l1, r1) == get(l2, r2)) puts("Yes");
        else puts("No");
    }
    
    return 0;
}
