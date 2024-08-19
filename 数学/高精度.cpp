const int N = 5005;
struct L
{
    array<ll, N> a{};
    int len = 0;
    L() {}
    L(ll x)
    {
        while (x)
        {
            a[len++] = x % 10;
            x /= 10;
        }
    }
    L(const string& s)
    {
        for (int i = 0; i < s.size(); ++i)
        {
            a[i] = s[s.size() - 1 - i] - '0';
            if (a[i]) len = max(len, i + 1);
        }
    }
    L& operator=(const L& rhs)
    {
        a = rhs.a;
        len = rhs.len;
        return *this;
    }
    L& operator+=(const L& rhs)
    {
        for (int i = 0; i < max(len, rhs.len); ++i)
        {
            a[i] += rhs.a[i];
            if (i + 1 < N) a[i + 1] += a[i] / 10;
            a[i] %= 10;
        }
        len = max(len, rhs.len);
        if (len < N && a[len]) len++;
        return *this;
    }
    L operator+(const L& rhs) const
    {
        L res(*this);
        res += rhs;
        return res;
    }
    L& operator-=(const L& rhs)
    {
        for (int i = 0; i < rhs.len; ++i) a[i] -= rhs.a[i];
        for (int i = 0; i < len; ++i)
        {
            if (a[i] < 0)
            {
                a[i] += 10;
                if (i + 1 < N) a[i + 1]--;
            }
        }
        while (len - 1 >= 0 && a[len - 1] == 0) len--;
        return *this;
    }
    L operator-(const L& rhs) const
    {
        L res(*this);
        res -= rhs;
        return res;
    }
    L& operator*=(const ll rhs)
    {
        if (rhs == 0)
        {
            *this = L();
            return *this;
        }
        for (int i = 0; i < len; ++i) a[i] *= rhs;
        for (int i = 0; i < min(len + 20, N); ++i)
        {
            if (i + 1 < N) a[i + 1] += a[i] / 10;
            a[i] %= 10;
            if (a[i]) len = max(len, i + 1);
        }
        return *this;
    }
    L operator*(const ll rhs) const
    {
        L res(*this);
        res *= rhs;
        return res;
    }
    L operator*(const L& rhs) const
    {
        if (rhs.len == 0) return L();
        L res;
        for (int i = 0; i < len; ++i)
        {
            for (int j = 0; j < rhs.len; ++j) res.a[i + j] += a[i] * rhs.a[j];
        }
        res.len = min(N, len + rhs.len - 1);
        for (int i = 0; i < res.len; ++i)
        {
            if (i + 1 < N) res.a[i + 1] += res.a[i] / 10;
            res.a[i] %= 10;
        }
        if (res.len < N && res.a[res.len]) res.len++;
        return res;
    }
    L& operator*=(const L& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    L& operator/=(const ll rhs)
    {
        assert(rhs);
        for (int i = len - 1; i >= 0; --i)
        {
            if (i - 1 >= 0) a[i - 1] += a[i] % rhs * 10;
            a[i] /= rhs;
        }
        while (len - 1 >= 0 && a[len - 1] == 0) len--;
        return *this;
    }
    L operator/(const ll rhs) const
    {
        L res(*this);
        res /= rhs;
        return res;
    }
    L operator/(const L& rhs) const
    {
        assert(rhs.len);
        if (*this < rhs) return L();
        L res, rem(*this);
        auto compare = [&](int i)
        {
            if (i + rhs.len < N && rem.a[i + rhs.len]) return true;
            for (int j = rhs.len - 1; j >= 0; --j)
            {
                if (rem.a[i + j] < rhs.a[j]) return false;
                else if (rem.a[i + j] > rhs.a[j]) return true;
            }
            return true;
        };
        for (int i = rem.len - rhs.len; i >= 0; --i)
        {
            while (compare(i))
            {
                res.a[i]++;
                res.len = max(res.len, i + 1);
                for (int j = 0; j < rhs.len; ++j)
                {
                    rem.a[i + j] -= rhs.a[j];
                    if (rem.a[i + j] < 0)
                    {
                        rem.a[i + j] += 10;
                        if (i + j + 1 < N) rem.a[i + j + 1]--;
                    }
                }
            }
        }
        while (rem.len - 1 >= 0 && rem.a[rem.len - 1] == 0) rem.len--;
        return res;
    }
    L& operator/=(const L& rhs)
    {
        *this = *this / rhs;
        return *this;
    }
    L operator%(const L& rhs) const
    {
        assert(rhs.len);
        if (*this < rhs) return *this;
        L res, rem(*this);
        auto compare = [&](int i)
        {
            if (i + rhs.len < N && rem.a[i + rhs.len]) return true;
            for (int j = rhs.len - 1; j >= 0; --j)
            {
                if (rem.a[i + j] < rhs.a[j]) return false;
                else if (rem.a[i + j] > rhs.a[j]) return true;
            }
            return true;
        };
        for (int i = rem.len - rhs.len; i >= 0; --i)
        {
            while (compare(i))
            {
                res.a[i]++;
                res.len = max(res.len, i + 1);
                for (int j = 0; j < rhs.len; ++j)
                {
                    rem.a[i + j] -= rhs.a[j];
                    if (rem.a[i + j] < 0)
                    {
                        rem.a[i + j] += 10;
                        if (i + j + 1 < N) rem.a[i + j + 1]--;
                    }
                }
            }
        }
        while (rem.len - 1 >= 0 && rem.a[rem.len - 1] == 0) rem.len--;
        return rem;
    }
    L& operator%=(const L& rhs)
    {
        *this = *this % rhs;
        return *this;
    }
    ll operator%(const ll rhs) const
    {
        ll res = 0;
        for (int i = N - 1; i >= 0; --i)
        {
            res = res * 10 + a[i];
            res %= rhs;
        }
        return res;
    }
    bool operator<(const L& rhs) const
    {
        if (len < rhs.len) return 1;
        else if (len > rhs.len) return 0;
        for (int i = len - 1; i >= 0; --i)
        {
            if (a[i] < rhs.a[i]) return 1;
            else if (a[i] > rhs.a[i]) return 0;
        }
        return 0;
    }
    bool operator>(const L& rhs) const
    {
        if (len > rhs.len) return 1;
        else if (len < rhs.len) return 0;
        for (int i = len - 1; i >= 0; --i)
        {
            if (a[i] > rhs.a[i]) return 1;
            else if (a[i] < rhs.a[i]) return 0;
        }
        return 0;
    }
    bool operator>=(const L& rhs) const { return !(*this < rhs); }
    bool operator<=(const L& rhs) const { return !(*this > rhs); }
    bool operator==(const L& rhs) const { return a == rhs.a; }
    static L p10(int p) { return L(string("1") + string(p, '0')); }
    L sqrt() const
    {
        L lef(0), rig(p10(len / 2 + 1));
        while (lef < rig - 1)
        {
            L mid = (lef + rig) / 2;
            if (mid * mid <= *this) lef = mid;
            else rig = mid;
        }
        return lef;
    }
};
ostream& operator<<(ostream& out, const L& rhs)
{
    if (rhs.len == 0)
    {
        out << '0';
        return out;
    }
    for (int i = rhs.len - 1; i >= 0; --i) out << rhs.a[i];
    return out;
}
istream& operator>>(istream& in, L& rhs)
{
    string s;
    in >> s;
    rhs = L(s);
    return in;
}