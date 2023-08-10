/*******************************************************************
* 时间复杂度：O(n)
* 说明：
* 1.筛出x以内所有质数
* 2.sieve[i]表征i是否为合数
* 3.prime中为升序排列的质数
*******************************************************************/
struct PrimeSieve
{
    vector<int> sieve;
    vector<ll> prime;

    void build(int x)
    {
        sieve.resize(x+1);
        sieve[1] = 1;
        for (int i = 2; i <= x; ++i)
        {
            if (sieve[i] == 0) prime.push_back(i);
            for (auto e : prime)
            {
                if (e > x / i) break;
                sieve[i * e] = 1;
                if (i % e == 0) break;
            }
        }
        return;
    }
};