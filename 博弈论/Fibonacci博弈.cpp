/*******************************************************************
* 时间复杂度：O(1)
* 说明：
* 1. 有一堆石子，两人轮流取。先手第一次不能直接取完。每次至少取一
* 个，但最多取上一个人的两倍。取走最后一个石子的人获胜。
* 2. 结论：是斐波那契数则先手必败，否则先手必胜。
*******************************************************************/
bool Fibonacci(ll x) //返回先手是否必胜
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