/*******************************************************************
* 时间复杂度：O(n)
* 说明：求每个数左边或右边第一个大于它的数的位置
*******************************************************************/
vector<int> stk;
for (int i = 1; i <= n; ++i)
{
    while (stk.size() && a[stk.back()] < a[i])
    {
        rig[stk.back()] = i;
        stk.pop_back();
    }
    if (stk.size()) lef[i] = stk.back();
    else lef[i] = 0;
    stk.push_back(i);
}
while (stk.size())
{
    rig[stk.back()] = n + 1;
    stk.pop_back();
}