/*******************************************************************
* 时间复杂度：插入O(b)/求最大异或和O(b)
* 说明：
* 1. 可以求子序列最大异或和
* 2. v中非零元素表示一组线性基
* 3. 线性基大小表征线性空间维数
* 4. 线性基中没有异或和为0的子集
* 5. 线性基中各数二进制最高位不同
*******************************************************************/
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