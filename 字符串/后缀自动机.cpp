/*******************************************************************
* 时间复杂度：O(n*ALPSZ)
* 说明：字符集较大可以将next换成map<char,int>
*******************************************************************/
struct SAM
{
    struct State
    {
        int maxlen; //结点代表的最长子串长度
        int link; //后缀链接，连向不在该点中的最长后缀
        vector<int> next;
        State(): maxlen(0), link(-1) { next.resize(26); }
    };
    vector<State> node;
    vector<ll> cnt; //子串出现次数（endpos集合大小）
    int now; //接收上一个字符到达的结点
    int size; //当前结点个数

    inline int F(char c) { return c - 'a'; }

    SAM(int x)
    {
        node.resize(x * 2 + 5);
        cnt.resize(x * 2 + 5);
        now = 0; //从根节点开始转移
        size = 1; //建立一个代表空串的根节点
    }

    void extend(char c)
    {
        int nid = size++;
        cnt[nid] = 1;
        node[nid].maxlen = node[now].maxlen + 1;
        int p = now;
        while (p != -1 && node[p].next[F(c)] == 0)
        {
            node[p].next[F(c)] = nid;
            p = node[p].link;
        }
        if (p == -1) node[nid].link = 0; //连向根结点
        else
        {
            int ori = node[p].next[F(c)];
            if (node[p].maxlen + 1 == node[ori].maxlen) node[nid].link = ori;
            else
            {
                //将ori结点的一部分拆出来分成新结点split
                int split = size++;
                node[split].maxlen = node[p].maxlen + 1;
                node[split].link = node[ori].link;
                node[split].next = node[ori].next;
                while (p != -1 && node[p].next[F(c)] == ori)
                {
                    node[p].next[F(c)] = split;
                    p = node[p].link;
                }
                node[ori].link = node[nid].link = split;
            }
        }
        now = nid;
        return;
    }

    void build(const string& s)
    {
        for (auto e : s) extend(e);
        return;
    }

    void DFS(int x, vector<vector<int>>& son)
    {
        for (auto e : son[x])
        {
            DFS(e, son);
            cnt[x] += cnt[e]; //link树上父节点endpos为所有子结点endpos之和
        }
        return;
    }

    void count() //计算endpos大小
    {
        //建立link树
        vector<vector<int>> son(size);
        for (int i = 1; i < size; ++i) son[node[i].link].push_back(i);

        //在link树上dfs
        DFS(0, son);
        return;
    }

    ll substr() //本质不同子串个数
    {
        ll res = 0;
        for (int i = 1; i < size; ++i)
        {
            res += node[i].maxlen - node[node[i].link].maxlen;
        }
        return res;
    }
};