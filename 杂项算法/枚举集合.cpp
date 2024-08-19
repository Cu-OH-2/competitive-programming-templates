struct EnumSet
{
    vector<int> subset(int x) // 枚举x的子集
    {
        vector<int> res;
        for (int i = x; i >= 1; i = (i - 1) & x) res.push_back(i);
        res.push_back(0);
        return res;
    }

    vector<int> kset(int b, int k) // 枚举b位大小为k的集合
    {
        vector<int> res;
        int now = (1 << k) - 1;
        while (now < (1 << b))
        {
            res.push_back(now);
            int lowbit = now & -now;
            int x = now + lowbit;
            int y = ((now & ~x) / lowbit) >> 1;
            now = x | y;
        }
        return res;
    }

    vector<int> superset(int x, int b) // 枚举x的b位超集
    {
        vector<int> res;
        for (int i = x; i < (1 << b); i = (i + 1) | x) res.push_back(i);
        return res;
    }
};
