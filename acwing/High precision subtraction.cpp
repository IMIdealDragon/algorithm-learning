#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool cmp(vector<int>& A, vector<int>& B)
{
    if(A.size() != B.size()) return A.size() > B.size();
    for(int i = A.size() - 1; i >= 0; i--)
        if(A[i] != B[i])
            return A[i] > B[i];
            
    return true; // 这种情况属于两者相等了吧
}

vector<int> sub(vector<int>& A, vector<int>& B)
{
    vector<int> C;
    //保证了A是大于B的
    int t = 0;//借位
    
    for(int i = 0; i < A.size(); i++)//从最低位开始计算的  下标越小 所在位数越低
    {
        t = A[i] - t;
        if(i < B.size()) t -= B[i]; //位数还未大于B
        C.push_back((t + 10) % 10);//t无论正负 都能保证只留下相减的差值
        //判断是否借位
        if(t < 0) t = 1;
        else t = 0;
    }
    
    while(C.size() > 1 && C.back() == 0) C.pop_back(); //去掉前导0;
    return C;
}
int main()
{
    string a, b;
    vector<int> A, B;
    cin >> a >> b;
    for (int i = a.size() - 1; i >= 0; i -- ) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i -- ) B.push_back(b[i] - '0');
    
    vector<int> C;
    if (cmp(A, B)) C = sub(A, B); //A > B直接调用
    else C = sub(B, A), cout << '-';//A < B输出个负号

    for (int i = C.size() - 1; i >= 0; i -- ) cout << C[i];
    cout << endl;
    
    return 0;
}
