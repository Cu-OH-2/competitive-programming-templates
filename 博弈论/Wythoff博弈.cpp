bool Wythoff(ll x, ll y) // 返回先手是否必胜
{
    const double K = ((1.0 + sqrt(5.0)) / 2.0);
    ll res = abs(x - y) * K;
    return res != min(x, y);
}