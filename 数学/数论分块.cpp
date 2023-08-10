/*******************************************************************
* 时间复杂度：O(sqrt(n))
* 说明：k%i=k-k/i*i => sigma(k%i)=k*n-sigma(k/i*i)
*******************************************************************/
ll n, k;

int main()
{
    //求sigma[i=1,n](k%i)
    ll ans = 0;
    cin >> n >> k;
    for (ll lef = 1, rig; lef <= n; lef = rig + 1) //分块
    {
        if (k >= lef)
        {
            rig = min(n, k / (k / lef));
        }
        else //该区间大于k（余数都为k）
        {
            rig = n;
        }
        ans += k * (rig - lef + 1) - (k / lef) * (lef + rig) * (rig - lef + 1) / 2;
    }
    cout << ans << '\n';
    return 0;
}