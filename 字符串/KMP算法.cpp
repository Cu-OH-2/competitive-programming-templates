struct KMP
{
    string t;
    vector<int> next;

    KMP() {}
    KMP(const string& str) { init(str); }

    void init(const string& str)
    {
        t = str;
        next.resize(t.size() + 1);
        next[0] = -1;
        for (int i = 1; i <= t.size(); ++i)
        {
            int now = next[i - 1];
            while (now != -1 && t[i - 1] != t[now]) now = next[now];
            next[i] = now + 1;
        }
        return;
    }

    int first(const string& s)
    {
        int ps = 0, pt = 0;
        while (ps < s.size())
        {
            while (pt != -1 && s[ps] != t[pt]) pt = next[pt];
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
            while (pt != -1 && s[ps] != t[pt]) pt = next[pt];
            ps++, pt++;
            if (pt == t.size())
            {
                v.push_back(ps - t.size());
                pt = next[pt];
            }
        }
        return v;
    }
};