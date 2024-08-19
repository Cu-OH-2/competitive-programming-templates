struct Trie
{
    static const int ALPSZ = 26;
    vector<vector<int>> trie;
    vector<int> tag;
    // vector<vector<int>> out;

    int F(char c) { return c - 'a'; }

    Trie() { init(); }

    void init()
    {
        create();
        return;
    }
    int create()
    {
        trie.push_back(vector<int>(ALPSZ));
        tag.push_back(0);
        // out.push_back(vector<int>());
        return trie.size() - 1;
    }
    void insert(const string& t)
    {
        int now = 0;
        for (auto e : t)
        {
            if (!trie[now][F(e)]) 
            {
                int newNode = create();
                // out[now].push_back(F(e));
                trie[now][F(e)] = newNode;
            }
            now = trie[now][F(e)];
            tag[now]++;
        }
        return;
    }
    int count(const string& pre)
    {
        int now = 0;
        for (auto e : pre)
        {
            now = trie[now][F(e)];
            if (now == 0) return 0;
        }
        return tag[now];
    }
};