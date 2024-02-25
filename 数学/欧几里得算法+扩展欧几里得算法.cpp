/*******************************************************************
* 时间复杂度：O(logn)
* 说明：
* 1.欧几里得算法：求最大公因数
* 2.扩展欧几里得算法：求解ax+by=gcd(a,b)
* 3.由扩展欧几里得算法求出一组解x1,y1后，可得解集：
    x=x1+b/gcd(a,b)*k
    y=y1-a/gcd(a,b)*k;
    解出的x1不保证是最小正整数，需要手动调整。
* 4.ax+by=1有解=>1是gcd(a,b)倍数=>gcd(a,b)=1
* 5.扩展欧几里得还可以解同余方程求乘法逆元
* 6.拓展到ax+by=c：x的变化单元还是b/g，但要先乘以c/g
*******************************************************************/
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