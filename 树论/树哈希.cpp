/*******************************************************************
* 时间复杂度：O(nlogn)
* 说明：判断有根树同构。无根树可通过找重心转换为有根树。
*******************************************************************/
struct TreeHash
{
    int n, root;
    vector<vector<int>> node;
    vector<int> hav;
    map<vector<int>, int> mp;
    int ord = 0;

    void getTree(vector<int>& p)
    {
        n = p.size() - 1;
        node.clear();
        node.resize(n + 1);
        hav.clear();
        hav.resize(n + 1);
        root = -1;
        for (int i = 1; i <= n; ++i)
        {
            if (p[i])
            {
                node[p[i]].push_back(i);
                node[i].push_back(p[i]);
            }
            else root = i;
        }
        return;
    }

    void getD(int id, int pa, vector<int>& sz, vector<int>& d)
    {
        sz[id] = 1;
        int res = 0;
        for (auto e : node[id])
        {
            if (e != pa)
            {
                getD(e, id, sz, d);
                sz[id] += sz[e];
                res = max(res, sz[e]);
            }
        }
        if (id == root) d[id] = res;
        else d[id] = max(res, n - sz[id]);
        return;
    }

    vector<int> center()
    {
        vector<int> res;
        vector<int> sz(n + 1), d(n + 1);
        int mnn = n;
        getD(root, -1, sz, d);
        for (int i = 1; i <= n; ++i) mnn = min(mnn, d[i]);
        for (int i = 1; i <= n; ++i) if (d[i] == mnn) res.push_back(i);
        return res;
    }

    vector<int> hash(vector<int>& p)
    {
        vector<int> res;
        getTree(p);
        auto v = center();
        for (auto e : v) dfs(e, -1), res.push_back(hav[e]);
        sort(res.begin(), res.end());
        return res;
    }

    int hash(vector<int>& p, int root)
    {
        getTree(p);
        dfs(root, -1);
        return hav[root];
    }

    void dfs(int id, int pa)
    {
        vector<int> v;
        for (auto e : node[id])
        {
            if (e != pa)
            {
                dfs(e, id);
                v.push_back(hav[e]);
            }
        }
        sort(v.begin(), v.end());
        if (mp.count(v) == 0) mp[v] = ++ord;
        hav[id] = mp[v];
        return;
    }
};