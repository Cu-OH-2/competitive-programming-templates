/*******************************************************************
* 时间复杂度: 查找近似O(1)/合并近似O(1)
* 说明: 路径压缩/启发式合并保证时间复杂度
*******************************************************************/
struct DSU
{
    vector<int> f;
    vector<int> v; //集合大小
    DSU() {}
    DSU(int x) { init(x); }
    void init(int x)
    {
        f.resize(x + 1);
        v.resize(x + 1);
        for (int i = 1; i <= x; ++i) f[i] = i;
        for (int i = 1; i <= x; ++i) v[i] = 1;
        return;
    }
    int find(int id) { return f[id] == id ? id : f[id] = find(f[id]); }
    void merge(int x, int y)
    {
        int fx = find(x), fy = find(y);
        if (fx == fy) return;
        if (v[fx] > v[fy]) swap(fx, fy);
        f[fx] = fy;
        v[fy] += v[fx];
        return;
    }
};