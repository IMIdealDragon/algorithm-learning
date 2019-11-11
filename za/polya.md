https://blog.csdn.net/lianai911/article/details/47804663

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
 
int M,N;
 
int GCD(int a,int b)
{
    if(b == 0)
        return a;
    return GCD(b,a%b);
}
 
int main()
{
    while(~scanf("%d%d",&M,&N) && (M||N))
    {
        int sum = 0;
        for(int i = 1; i <= N; ++i)
        {
            int tmp = GCD(N,i);
            sum += (int)(pow(M*1.0,tmp*1.0));
        }
        if(N & 1)
            sum += (int)(N * pow(M*1.0, (N+1)/2.0));
        else
        {
            sum += (int)((N/2) * pow(M*1.0, (N+2)/2.0));
            sum += (int)((N/2) * pow(M*1.0, N/2.0));
        }
        sum = sum/(2*N);
        printf("%d\n",sum);
    }
 
    return 0;
}
```

