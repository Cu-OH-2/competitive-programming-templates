/*******************************************************************
* 时间复杂度: O(logn)
* 说明: 注意起始序号
*******************************************************************/
struct Discret
{
    vector<ll> v;
    void insert(ll val)
    {
        v.push_back(val);
        return;
    }
    void work()
    {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        return;
    }
    void clear()
    {
        v.clear();
        return;
    }
    ll operator[](ll val)
    {
        return lower_bound(v.begin(), v.end(), val) - v.begin();
    }
};