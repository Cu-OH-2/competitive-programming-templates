/*******************************************************************
* 时间复杂度: O(n)
* 说明：用n+1个分隔符将字符串分隔可以将奇偶回文子串过程统一处理
*******************************************************************/
struct Manacher
{
    vector<int> odd, even; //以[i]或[i,i+1]为中心的最长回文串半径
    void work(const string& s)
    {
        odd.resize(s.size());
        even.resize(s.size() - 1);
        int lef = 0, rig = -1, r;
        for (int i = 0; i < s.size(); ++i)
        {
            if (i > rig) r = 1;
            else r = min(odd[lef + rig - i], rig - i) + 1; //利用对称位置答案
            while (i - r >= 0 && i + r < s.size() && s[i - r] == s[i + r]) r++; //暴力扩展
            odd[i] = --r; //记录答案
            if (i + r > rig) lef = i - r, rig = i + r; //扩展lef,rig范围
        }
        lef = 0, rig = -1;
        for (int i = 0; i + 1 < s.size(); ++i)
        {
            if (i + 1 > rig) r = 1;
            else r = min(even[lef + rig - i - 1], rig - i) + 1;
            while (i + 1 - r >= 0 && i + r < s.size() && s[i + 1 - r] == s[i + r]) r++;
            even[i] = --r;
            if (i + r > rig) lef = i + 1 - r, rig = i + r;
        }
        return;
    }
};