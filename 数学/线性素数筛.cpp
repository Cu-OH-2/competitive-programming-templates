struct PrimeSieve
{
    vector<int> sieve;
    vector<ll> prime;

    void build(int x)
    {
        sieve.resize(x + 1);
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