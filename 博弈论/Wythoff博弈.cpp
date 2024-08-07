/*******************************************************************
* 时间复杂度：O(1)
* 说明：
* 1. 有两堆石子，两人轮流取。每次可以在一堆中取任意个石子或在两堆中取同
*   样多的任意个石子，取走最后一个石子的人获胜。
* 2. 若x和y极大则需要注意精度问题。
*******************************************************************/
bool Wythoff(ll x, ll y) //返回先手是否必胜
{
    const double K = ((1.0 + sqrt(5.0)) / 2.0);
    ll res = abs(x - y) * K;
    return res != min(x, y);
}