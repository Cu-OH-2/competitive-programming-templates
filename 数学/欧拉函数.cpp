/*******************************************************************
* 时间复杂度: O(sqrt(n))
* 说明: 
* 1.欧拉函数的性质：
* I.phi(x)=x*Π((p[i]-1)/p[i])，p[i]为x的第i个质因数；
* II.若x为质数：
*   i%x==0 => phi(i*x)=x*phi(i)
*   i%x!=0 => phi(i*x)=(x-1)*phi(i)
* 2.若求[l,r]内的欧拉函数，可以先筛出sqrt(r)以内的质数，用这些质数
* 贡献范围内的数，再特判所有数sqrt(r)以上的质因子即可，类似素数筛。
*******************************************************************/
//求n的欧拉函数，类似于质因数分解
int phi(int n)
{
    int res = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0) res = res / i * (i - 1);
        while (n % i == 0) n /= i;
    }
    if (n > 1) res = res / n * (n - 1);
    return res;
}