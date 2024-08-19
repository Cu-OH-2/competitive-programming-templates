ll qpow(ll a, ll p, ll mod)
{
    ll res = 1;
    while (p)
    {
        if (p & 1) res = res * a % mod;
        a = a * a % mod;
        p >>= 1
    }
    return res;
}

ll inv(ll a, ll mod)
{
    return qpow(a, mod - 2, mod);
}