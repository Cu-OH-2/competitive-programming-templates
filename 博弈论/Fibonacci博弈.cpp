bool Fibonacci(ll x) // 返回先手是否必胜
{
    ll a = 1, b = 1;
    while (max(a, b) <= x)
    {
        if (a < b) a += b;
        else b += a;
        if (max(a, b) == x) return 0;
    }
    return 1;
}