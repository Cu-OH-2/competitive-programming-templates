struct BarretReduction
{
    ll m, p;
    void init(int mod)
    {
        m = ((__int128)1 << 64) / mod;
        p = mod;
    }
    ll operator()(ll x) { return x - ((__int128(x) * m) >> 64) * p; }
} br;

ll qmod(ll a, ll b, ll mod) { return a * b - ll(ld(a) / mod * b + 1e-8) * mod; }