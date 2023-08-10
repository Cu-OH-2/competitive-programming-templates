/*******************************************************************
* 时间复杂度：O(n)
* 说明：
* 1.每个结点代表一个本质不同回文串。link链：多字串->单字符->偶根->奇根。
* 2.每个本质不同回文子串次数：最后由母串向子串传递。
    每个前缀的后缀回文子串个数：新建时由最长回文后缀向新串传递。
*******************************************************************/
struct PAM
{
    struct State
    {
        int len; //长度
        int link; //最长回文后缀结点
        vector<int> next; //两边加上某字符时对应的结点
        State() { next.resize(26); }
        State(int x, int y): len(x), link(y) { next.resize(26); }
    };
    vector<State> node;
    vector<ll> cnt; //本质不同回文串出现次数
    int now; //接收上一个字符到达的结点
    int size; //当前结点个数

    inline int F(char c) { return c - 'a'; }

    PAM(int x)
    {
        node.resize(x + 3);
        node[0] = State(-1, 0); //奇根，link无意义
        node[1] = State(0, 0); //偶根，link指向奇根
        cnt.resize(x + 3);
        now = 0; //第一个字符由奇根转移
        size = 2;
    }

    void build(const string& s)
    {
        auto find = [&](int x, int p) //寻找x后缀中左方为s[p]的最长回文子串
        {
            while (p - node[x].len - 1 < 0 || s[p] != s[p - node[x].len - 1]) x = node[x].link;
            return x;
        };
        for (int i = 0; i < s.size(); ++i)
        {
            now = find(now, i);
            if (!node[now].next[F(s[i])]) //对应结点不存在则需要新建
            {
                int nid = size++;
                node[nid].len = node[now].len + 2; //新建状态结点
                node[nid].link = 1; //若now=0，对应结点为单字符，指向偶根
                if (now) node[nid].link = node[find(node[now].link, i)].next[F(s[i])]; //否则指向再前一个结点的扩展
                node[now].next[F(s[i])] = nid;
            }
            now = node[now].next[F(s[i])];
            cnt[now]++;
        }
        for (int i = size - 1; i >= 2; --i) cnt[node[i].link] += cnt[i]; //数量由母串向子串传递
        return;
    }
};