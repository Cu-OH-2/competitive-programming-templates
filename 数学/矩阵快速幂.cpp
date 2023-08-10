/*******************************************************************
* 时间复杂度：O(n^3logp)
* 说明：已知递推式可以表示为矩阵乘法，快速求数列第i项
*******************************************************************/
const int MOD = 1e9 + 7;

struct Square
{
    int n;
    vector<vector<ll>> a;
    Square(int n): n(n) { a.resize(n, vector<ll>(n)); }
    void unit()
    {
        for (int i = 0; i < n; ++i)
        {
            a[i][i] = 1;
        }
        return;
    }
};

Square mult(const Square& lhs, const Square& rhs)
{
    assert(lhs.n == rhs.n);
    int n = lhs.n;
    Square res(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                res.a[i][j] += lhs.a[i][k] * rhs.a[k][j] % MOD;
                res.a[i][j] %= MOD;
            }
        }
    }
    return res;
}

Square qpow(Square a, ll p)
{
    int n = a.n;
    Square res(n);
    res.unit();
    while (p)
    {
        if (p & 1) res = mult(res, a);
        a = mult(a, a);
        p >>= 1;
    }
    return res;
}