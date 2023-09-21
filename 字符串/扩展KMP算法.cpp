/*******************************************************************
* 时间复杂度: O(n)
* 说明：
* 1.Z函数代表后缀与母串的最长公共前缀
* 2.还可以求模式串与文本串每个后缀的LCP
*******************************************************************/
struct ExKMP
{
    string t;
    vector<int> z;

    ExKMP(const string& str)
    {
        t = str;
        z.resize(t.size());
        z[0] = t.size();
        int l = 0, r = -1;
        for (int i = 1; i < t.size(); ++i) 
        {
            if (i <= r && z[i - l] < r - i + 1) z[i] = z[i - l];
            else 
            {
                z[i] = max(0, r - i + 1);
                while (i + z[i] < t.size() && t[z[i]] == t[i + z[i]]) z[i]++;
            }
            if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }
    }

    vector<int> ext(const string& s)
    {
        vector<int> res(s.size());
        int l = 0, r = -1;
        for (int i = 0; i < s.size(); ++i)
        {
            if (i <= r && z[i - l] < r - i + 1) res[i] = z[i - l];
            else
            {
                res[i] = max(0, r - i + 1);
                while (i + res[i] < s.size() && res[i] < t.size() && t[res[i]] == s[i + res[i]]) res[i]++;
            }
            if (i + res[i] - 1 > r) l = i, r = i + res[i] - 1;
        }
        return res;
    }
};