ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}

ll exgcd(ll a, ll b, ll& x, ll& y)
{
    if (b == 0) { x = 1, y = 0; return a; }
    ll d = exgcd(b, a % b, x, y);
    ll newx = y, newy = x - a / b * y;
    x = newx, y = newy;
    return d;
}

ll inv(ll a, ll mod)
{
    ll x, y;
    exgcd(a, mod, x, y);
    return x;
}

ll a, b, x, y, g;

void solve()
{
    cin >> a >> b;
    g = exgcd(a, b, x, y);
    auto M = [](ll x, ll m) {return (x % m + m) % m; };
    cout << M(x, b / g) << '\n';
    return;
}