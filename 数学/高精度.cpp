/*******************************************************************
* 时间复杂度：O(n)/O(n^2)
* 说明：待完善，注意复杂度
*******************************************************************/
const int N = 5005;

struct Large
{
    array<ll, N> ar{};
    int len = 0;
    Large() {}
    Large(ll x)
    {
        int p = 0;
        while (x)
        {
            ar[p++] = x % 10;
            x /= 10;
        }
        updateLen();
    }
    Large(const string& s)
    {
        for (int i = 0; i < s.size(); ++i)
        {
            ar[i] = s[s.size() - 1 - i] - '0';
        }
        updateLen();
    }

    void updateLen()
    {
        len = ar.size();
        for (int i = ar.size() - 1; i >= 0; --i)
        {
            if (ar[i]) break;
            len = i;
        }
        return;
    }

    Large& operator=(const Large& rhs)
    {
        for (int i = 0; i < ar.size(); ++i) ar[i] = rhs.ar[i];
        updateLen();
        return *this;
    }

    Large operator+(const Large& rhs) const
    {
        Large res;
        for (int i = 0; i < ar.size(); ++i) res.ar[i] = ar[i] + rhs.ar[i];
        for (int i = 0; i < ar.size() - 1; ++i)
        {
            res.ar[i + 1] += res.ar[i] / 10;
            res.ar[i] %= 10;
        }
        res.updateLen();
        return res;
    }

    Large& operator+=(const Large& rhs)
    {
        for (int i = 0; i < ar.size(); ++i) ar[i] += rhs.ar[i];
        for (int i = 0; i < ar.size() - 1; ++i)
        {
            ar[i + 1] += ar[i] / 10;
            ar[i] %= 10;
        }
        updateLen();
        return *this;
    }

    Large operator-(const Large& rhs) const
    {
        Large res;
        for (int i = 0; i < ar.size(); ++i) res.ar[i] = ar[i] - rhs.ar[i];
        for (int i = 0; i < ar.size() - 1; ++i)
        {
            if (res.ar[i] < 0)
            {
                res.ar[i] += 10;
                res.ar[i + 1]--;
            }
        }
        res.updateLen();
        return res;
    }

    Large operator*(const ll rhs) const
    {
        Large res;
        for (int i = 0; i < ar.size(); ++i) res.ar[i] = ar[i] * rhs;
        for (int i = 0; i < ar.size() - 1; ++i)
        {
            if (res.ar[i] > 9)
            {
                res.ar[i + 1] += res.ar[i] / 10;
                res.ar[i] %= 10;
            }
        }
        res.updateLen();
        return res;
    }

    Large& operator*=(const ll rhs)
    {
        for (int i = 0; i < ar.size(); ++i) ar[i] *= rhs;
        for (int i = 0; i < ar.size() - 1; ++i)
        {
            if (ar[i] > 9)
            {
                ar[i + 1] += ar[i] / 10;
                ar[i] %= 10;
            }
        }
        updateLen();
        return *this;
    }

    Large operator*(const Large& rhs) const
    {
        Large res;
        Large dup = *this;
        for (int i = 0; i < rhs.len; ++i)
        {
            res += dup * rhs.ar[i];
            dup *= 10;
        }
        return res;
    }

    Large& operator*=(const Large& rhs)
    {
        *this = *this * rhs;
        return *this;
    }
};

ostream& operator<<(ostream& out, const Large& large)
{
    if (large.len == 0)
    {
        out << '0';
        return out;
    }
    for (int i = large.len - 1; i >= 0; --i) out << large.ar[i];
    return out;
}