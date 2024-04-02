/*******************************************************************
* 时间复杂度: O(n)
* 说明：
* 1. 字符串下标从0开始
* 2. nxt[i]表示t[i]失配时下一次匹配的位置
* 3. nxt[n]在匹配中无必要作用，但构成前缀数组
* 4. 前缀数组pi[i]=nxt[i+1]+1，代表前缀t[0,i]的最长前后缀长度
*******************************************************************/
struct KMP
{
    string t;
    vector<int> nxt;

    KMP() {}
    KMP(const string& str) { init(str); }

    void init(const string& str)
    {
        t = str;
        nxt.resize(t.size() + 1);
        nxt[0] = -1;
        for (int i = 1; i <= t.size(); ++i)
        {
            int now = nxt[i - 1];
            while (now != -1 && t[i - 1] != t[now]) now = nxt[now];
            nxt[i] = now + 1;
        }
        return;
    }

    int first(const string& s)
    {
        int ps = 0, pt = 0;
        while (ps < s.size())
        {
            while (pt != -1 && s[ps] != t[pt]) pt = nxt[pt];
            ps++, pt++;
            if (pt == t.size()) return ps - t.size();
        }
        return -1;
    }

    vector<int> every(const string& s)
    {
        vector<int> v;
        int ps = 0, pt = 0;
        while (ps < s.size())
        {
            while (pt != -1 && s[ps] != t[pt]) pt = nxt[pt];
            ps++, pt++;
            if (pt == t.size())
            {
                v.push_back(ps - t.size());
                pt = nxt[pt];
            }
        }
        return v;
    }
};