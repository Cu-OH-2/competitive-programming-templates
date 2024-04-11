/*******************************************************************
* 时间复杂度：O(nm)
* 说明：递推预处理组合数：C[i][j]=C[i-1][j-1]+C[i-1][j]
*******************************************************************/
struct Comb
{
    vector<vector<ll>> c;
    Comb(int x, int y, int mod)
    {
        c.resize(x + 1, vector<ll>(y + 1));
        for (int i = 0; i <= x; ++i) c[i][0] = 1;
        for (int i = 1; i <= x; ++i)
        {
            for (int j = 1; j <= i; ++j) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
        }
    }
    ll val(int x, int y)
    {
        if (x < 0 || y < 0) return 0;
        else return c[x][y];
    }
};