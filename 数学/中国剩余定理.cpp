struct CRT
{
    vector<pair<ll, ll>> f;
    inline ll nrm(ll x, ll mod) { return (x % mod + mod) % mod; }
    ll exgcd(ll a, ll b, ll& x, ll& y)
    {
        if (b == 0)
        {
            x = 1, y = 0;
            return a;
        }
        ll d = exgcd(b, a % b, x, y);
        ll newx = y, newy = x - a / b * y;
        x = newx, y = newy;
        return d;
    }
    ll inv(ll a, ll mod)
    {
        ll x, y;
        exgcd(a, mod, x, y);
        return nrm(x, mod);
    }
    void insert(ll r, ll m)
    {
        f.push_back({ r, m });
        return;
    }
    ll work()
    {
        ll mul = 1, ans = 0;
        for (auto e : f) mul *= e.second;
        for (auto e : f)
        {
            ll m = mul / e.second;
            ll c = m * inv(m, e.second);
            ans += c * e.first;
        }
        return nrm(ans, mul);
    }
};