struct ACAM
{
    static const int ALPSZ = 26;

    vector<vector<int>> trie; // trie树指针
    vector<int> tag; // 标记数组
    vector<int> fail; // 失配函数
    vector<int> last; // 跳转路径上一个模式串结点
    vector<int> cnt; // 计数器
    int ord; // 结点个数
    
    int F(char c) { return c - 'a'; }

    ACAM() { init(); }

    void init()
    {
        ord = -1;
        newNode();
    }
    int newNode()
    {
        trie.push_back(vector<int>(ALPSZ));
        tag.push_back(0);
        return ++ord;
    }
    void addPat(const string& t)
    {
        int now = 0;
        for (auto e : t)
        {
            if (!trie[now][F(e)]) trie[now][F(e)] = newNode();
            now = trie[now][F(e)];
        }
        tag[now]++;
        return;
    }
    void buildAM()
    {
        fail.resize(ord + 1);
        last.resize(ord + 1);
        cnt.resize(ord + 1);
        queue<int> q;
        for (int i = 0; i < ALPSZ; ++i)
        {
            // 第一层结点的fail指针都指向0，不需要处理
            if (trie[0][i]) q.push(trie[0][i]);
        }
        while (q.size())
        {
            int now = q.front();
            q.pop();
            for (int i = 0; i < ALPSZ; ++i)
            {
                int son = trie[now][i];
                if (son)
                {
                    fail[son] = trie[fail[now]][i];
                    if (tag[fail[son]]) last[son] = fail[son];
                    else last[son] = last[fail[son]];
                    q.push(trie[now][i]);
                }
                else trie[now][i] = trie[fail[now]][i];
            }
        }
        return;
    }
    int count(const string& s)
    {
        int now = 0, ans = 0;
        for (auto e : s)
        {
            now = trie[now][F(e)];
            int p = now;
            while (p)
            {
                ans += tag[p];
                p = last[p];
            }
        }
        return ans;
    }
};