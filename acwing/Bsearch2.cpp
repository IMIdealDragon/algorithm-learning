#include <iostream>
using namespace std;
int main()
{
    double n = 0;
    cin >> n;
    
    double l = -100, r = 100;
    while(r - l > 1e-8)
    {
        double mid = (r + l) / 2;
        if(mid * mid * mid >= n) r = mid;
        else l = mid;
    }
    
    printf("%6lf",l);
    return 0;
}

//链接：https://www.acwing.com/problem/content/792/