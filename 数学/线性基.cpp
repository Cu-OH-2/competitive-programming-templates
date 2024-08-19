const int N = 55;
const int B = 50;

template<int bit>
struct LinearBasis
{
    vector<ll> v;
    LinearBasis() { v.resize(bit); }
    void insert(ll x)
    {
        for (int i = bit - 1; i >= 0; --i)
        {
            if (x >> i & 1ll)
            {
                if (v[i]) x ^= v[i];
                else
                {
                    v[i] = x;
                    break;
                }
            }
        }
        return;
    }
    ll qmax()
    {
        ll res = 0;
        for (int i = bit - 1; i >= 0; --i)
        {
            if ((res ^ v[i]) > res) res ^= v[i];
        }
        return res;
    }
    void merge(const LinearBasis<bit>& b)
    {
        for (auto e : b.v) insert(e);
        return;
    }
};