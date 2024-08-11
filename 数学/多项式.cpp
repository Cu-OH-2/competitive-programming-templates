/*******************************************************************
* 时间复杂度：O(nlogn)
* 说明：from jiangly
*******************************************************************/
constexpr int MOD = 998244353;

int nrm(int x)
{
    // assume -MOD <= x < 2MOD
    if (x < 0) x += MOD;
    if (x >= MOD) x -= MOD;
    return x;
}

template<class T> T power(T a, ll b)
{
    T res = 1;
    for (; b; b /= 2, a *= a)
    {
        if (b % 2) res *= a;
    }
    return res;
}

struct Z
{
    int x;
    Z(int x = 0): x(nrm(x)) {}
    Z(ll x): x(nrm(x % MOD)) {}
    int val() const { return x; }
    Z operator-() const { return Z(nrm(MOD - x)); }
    Z inv() const
    {
        assert(x != 0);
        return power(*this, MOD - 2);
    }
    Z& operator*=(const Z& rhs)
    {
        x = ll(x) * rhs.x % MOD;
        return *this;
    }
    Z& operator+=(const Z& rhs)
    {
        x = nrm(x + rhs.x);
        return *this;
    }
    Z& operator-=(const Z& rhs)
    {
        x = nrm(x - rhs.x);
        return *this;
    }
    Z& operator/=(const Z& rhs) { return *this *= rhs.inv(); }
    friend Z operator*(const Z& lhs, const Z& rhs)
    {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z& lhs, const Z& rhs)
    {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z& lhs, const Z& rhs)
    {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z& lhs, const Z& rhs)
    {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend istream& operator>>(istream& is, Z& a)
    {
        ll v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend ostream& operator<<(ostream& os, const Z& a) { return os << a.val(); }
};

vector<int> rev;
vector<Z> roots{ 0, 1 };

void dft(vector<Z>& a)
{
    int n = a.size();

    if (rev.size() != n)
    {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++) rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
    }

    for (int i = 0; i < n; i++)
    {
        if (rev[i] < i) swap(a[i], a[rev[i]]);
    }
    if (roots.size() < n)
    {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n)
        {
            Z e = power(Z(3), (MOD - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++)
            {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = roots[i] * e;
            }
            k++;
        }
    }
    for (int k = 1; k < n; k *= 2)
    {
        for (int i = 0; i < n; i += 2 * k)
        {
            for (int j = 0; j < k; j++)
            {
                Z u = a[i + j];
                Z v = a[i + j + k] * roots[k + j];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
    return;
}

void idft(vector<Z>& a)
{
    int n = a.size();
    reverse(a.begin() + 1, a.end());
    dft(a);
    Z inv = (1 - MOD) / n;
    for (int i = 0; i < n; i++) a[i] *= inv;
    return;
}

struct Poly
{
    vector<Z> a;
    Poly() {}
    explicit Poly(int size): a(size) {}
    Poly(const vector<Z>& a): a(a) {}
    Poly(const initializer_list<Z>& a): a(a) {}
    int size() const { return a.size(); }
    void resize(int n) { a.resize(n); }
    Z operator[](int idx) const
    {
        if (idx < size()) return a[idx];
        else return 0;
    }
    Z& operator[](int idx) { return a[idx]; }
    Poly mulxk(int k) const
    {
        auto b = a;
        b.insert(b.begin(), k, 0);
        return Poly(b);
    }
    Poly modxk(int k) const
    {
        k = min(k, size());
        return Poly(vector<Z>(a.begin(), a.begin() + k));
    }
    Poly divxk(int k) const
    {
        if (size() <= k) return Poly();
        return Poly(vector<Z>(a.begin() + k, a.end()));
    }
    friend Poly operator+(const Poly& a, const Poly& b)
    {
        vector<Z> res(max(a.size(), b.size()));
        for (int i = 0; i < res.size(); i++) res[i] = a[i] + b[i];
        return Poly(res);
    }
    friend Poly operator-(const Poly& a, const Poly& b)
    {
        vector<Z> res(max(a.size(), b.size()));
        for (int i = 0; i < res.size(); i++) res[i] = a[i] - b[i];
        return Poly(res);
    }
    friend Poly operator-(const Poly& a)
    {
        vector<Z> res(a.size());
        for (int i = 0; i < res.size(); i++) res[i] = -a[i];
        return Poly(res);
    }
    friend Poly operator*(Poly a, Poly b)
    {
        if (a.size() == 0 || b.size() == 0) return Poly();
        if (a.size() < b.size()) swap(a, b);
        if (b.size() < 128)
        {
            Poly c(a.size() + b.size() - 1);
            for (int i = 0; i < a.size(); i++)
            {
                for (int j = 0; j < b.size(); j++) c[i + j] += a[i] * b[j];
            }
            return c;
        }
        int sz = 1, tot = a.size() + b.size() - 1;
        while (sz < tot) sz *= 2;
        a.a.resize(sz);
        b.a.resize(sz);
        dft(a.a);
        dft(b.a);
        for (int i = 0; i < sz; ++i) a.a[i] = a[i] * b[i];
        idft(a.a);
        a.resize(tot);
        return a;
    }
    friend Poly operator*(Z a, Poly b)
    {
        for (int i = 0; i < b.size(); i++) b[i] *= a;
        return b;
    }
    friend Poly operator*(Poly a, Z b)
    {
        for (int i = 0; i < a.size(); i++) a[i] *= b;
        return a;
    }
    Poly& operator+=(Poly b) { return (*this) = (*this) + b; }
    Poly& operator-=(Poly b) { return (*this) = (*this) - b; }
    Poly& operator*=(Poly b) { return (*this) = (*this) * b; }
    Poly& operator*=(Z b) { return (*this) = (*this) * b; }
    Poly deriv() const
    {
        if (a.empty()) return Poly();
        vector<Z> res(size() - 1);
        for (int i = 0; i < size() - 1; ++i) res[i] = (i + 1) * a[i + 1];
        return Poly(res);
    }
    Poly integr() const
    {
        vector<Z> res(size() + 1);
        for (int i = 0; i < size(); ++i) res[i + 1] = a[i] / (i + 1);
        return Poly(res);
    }
    Poly inv(int m) const
    {
        Poly x{ a[0].inv() };
        int k = 1;
        while (k < m)
        {
            k *= 2;
            x = (x * (Poly{ 2 } - modxk(k) * x)).modxk(k);
        }
        return x.modxk(m);
    }
    Poly log(int m) const { return (deriv() * inv(m)).integr().modxk(m); }
    Poly exp(int m) const
    {
        Poly x{ 1 };
        int k = 1;
        while (k < m)
        {
            k *= 2;
            x = (x * (Poly{ 1 } - x.log(k) + modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }
    Poly pow(int k, int m) const
    {
        int i = 0;
        while (i < size() && a[i].val() == 0) i++;
        if (i == size() || 1LL * i * k >= m) return Poly(vector<Z>(m));
        Z v = a[i];
        auto f = divxk(i) * v.inv();
        return (f.log(m - i * k) * k).exp(m - i * k).mulxk(i * k) * power(v, k);
    }
    Poly sqrt(int m) const
    {
        Poly x{ 1 };
        int k = 1;
        while (k < m)
        {
            k *= 2;
            x = (x + (modxk(k) * x.inv(k)).modxk(k)) * ((MOD + 1) / 2);
        }
        return x.modxk(m);
    }
    Poly mulT(Poly b) const
    {
        if (b.size() == 0) return Poly();
        int n = b.size();
        reverse(b.a.begin(), b.a.end());
        return ((*this) * b).divxk(n - 1);
    }
    vector<Z> eval(vector<Z> x) const
    {
        if (size() == 0) return vector<Z>(x.size(), 0);
        const int n = max(int(x.size()), size());
        vector<Poly> q(4 * n);
        vector<Z> ans(x.size());
        x.resize(n);
        function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            if (r - l == 1) q[p] = Poly{ 1, -x[l] };
            else
            {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        function<void(int, int, int, const Poly&)> work = [&](int p, int l, int r, const Poly& num)
        {
            if (r - l == 1)
            {
                if (l < ans.size()) ans[l] = num[0];
            }
            else
            {
                int m = (l + r) / 2;
                work(2 * p, l, m, num.mulT(q[2 * p + 1]).modxk(m - l));
                work(2 * p + 1, m, r, num.mulT(q[2 * p]).modxk(r - m));
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};