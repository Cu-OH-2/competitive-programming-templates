/*******************************************************************
* 时间复杂度: O(alpsz*sigma(len(t))+len(s))
* 说明：
* 1.本模板以小写英文字母为字母表举例，修改字母表可以通过修改F()函数完成。
* 2.Trie图优化：建立fail指针时，fail指针指向的结点有可能依然失配，需要多
*   次跳转才能到达匹配结点。可以将所有结点的空指针补全，置为该结点的跳转
*   终点。此时根据BFS序，在计算tr[x][i]的fail指针时，fail[x]一定已遍历
*   过，且tr[fail[x]][i]一定存在，要么为fail[x]接收i的后继状态，要么为
*   tr[x][i]的跳转终点。无论哪种情况，fail[tr[x][i]]都可以直接置为
*   tr[fail[x]][i]。
* 3.last优化：多模式匹配过程中，对于文本串的每个前缀s'，沿fail指针路径寻
*   找为s'后缀的模式串，途中可能经过无贡献的模式串真前缀结点；last优化使
*   得跳转时跳过真前缀结点直接到达上方第一个模式串结点。last数组可以完全
*   替代fail数组。
* 4.树上差分优化：统计每种模式串出现次数时，每匹配到一个模式串都要向上跳
*   转一次，这个过程相当于区间加一，可以用更新差分数组代替，最后再计算前
*   缀和即可。
*******************************************************************/
struct ACAM
{
    vector<vector<int>> trie; //trie树指针
    vector<int> tag; //标记数组
    vector<int> fail; //失配函数
    vector<int> last; //跳转路径上一个模式串结点
    vector<int> cnt; //计数器
    const int ALPSZ = 26; //字母表大小
    int ord; //结点个数

    inline int F(char c) { return c - 'a'; }

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
        for (int i = 0; i < 26; ++i)
        {
            //第一层结点的fail指针都指向0，不需要处理
            if (trie[0][i]) q.push(trie[0][i]);
        }
        while (q.size())
        {
            int now = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i)
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
    int count(const string& s) //统计出现的模式串种数
    {
        int now = 0, ans = 0;
        for (auto e : s)
        {
            now = trie[now][F(e)];
            int p = now;
            while (p) //累加树上差分
            {
                ans += tag[p];
                p = last[p];
            }
        }
        return ans;
    }
};