struct ConInv
{
    vector<ll> inv;
    ConInv(int sz, ll mod)
    {
        inv.resize(sz);
        inv[1] = 1;
        for (int i = 2; i <= sz; ++i)
        {
            inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        }
    }
};