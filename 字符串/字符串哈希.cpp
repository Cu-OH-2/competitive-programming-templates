const int M1 = 998244389;
const int M2 = 998244391;
const int B = 257;
const int N = 1000005;

struct Base
{
    array<ll, N> pow{};
    Base(int mod)
    {
        pow[0] = 1;
        for (int i = 1; i <= N - 1; ++i) pow[i] = pow[i - 1] * B % mod;
    }
    const ll operator[](int idx) const { return pow[idx]; }
} p1(M1), p2(M2);

struct Hash
{
    vector<ll> hash1, hash2;
    void build(const string& s)
    {
        int n = s.size() - 1;
        hash1.resize(n + 1);
        hash2.resize(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            hash1[i] = (hash1[i - 1] * B % M1 + s[i] - 'a' + 1) % M1;
            hash2[i] = (hash2[i - 1] * B % M2 + s[i] - 'a' + 1) % M2;
        }
        return;
    }
    ll merge(ll x, ll y) { return x << 31 | y; }
    ll calc(int lef, int rig)
    {
        ll res1 = (hash1[rig] - hash1[lef - 1] * p1[rig - lef + 1] % M1 + M1) % M1;
        ll res2 = (hash2[rig] - hash2[lef - 1] * p2[rig - lef + 1] % M2 + M2) % M2;
        return merge(res1, res2);
    }
};