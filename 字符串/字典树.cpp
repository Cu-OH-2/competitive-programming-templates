/*******************************************************************
* 时间复杂度：O(sigma(n))
* 说明：
* 1.字典树也即前缀树，每个结点代表一个前缀
* 2.字母表变化只需要修改映射函数F()
* 3.若需要遍历trie树可以用out数组记录出边降低复杂度
*******************************************************************/
struct Trie
{
    const int ALPSZ = 26;
    vector<vector<int>> trie;
    vector<int> tag;
    //vector<vector<int>> out;

    inline int F(char c) { return c - 'a'; }

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
        //out.push_back(vector<int>());
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
                //out[now].push_back(F(e));
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