/*******************************************************************
* 时间复杂度：O(nlogn)
* 说明：两倍常数，但跳过所有与基准相等的值
*******************************************************************/
const int N = 100005;

int n;
ll a[N];

int median(int x, int y, int z)
{
    if (a[x] > a[y] && a[z] > a[y]) return a[x] > a[z] ? z : x;
    else if (a[x] < a[y] && a[z] < a[y]) return a[x] < a[z] ? z : x;
    else return y;
}

void QuickSort(int lef, int rig)//[lef, rig]
{
    if (rig <= lef) return;
    int mid = lef + (rig - lef) / 2;
    int pivot = median(lef, mid, rig);
    swap(a[pivot], a[lef]);
    int lp = lef; //第一个等于基准的值
    for (int i = lef + 1; i <= rig; ++i)
    {
        if (a[i] < a[lef]) swap(a[i], a[++lp]);
    }
    swap(a[lef], a[lp]);
    int rp = lp; //最后一个等于基准的值
    for (int i = lp + 1; i <= rig; ++i)
    {
        if (a[i] == a[lp]) swap(a[i], a[++rp]);
    }
    QuickSort(lef, lp - 1);
    QuickSort(rp + 1, rig);
    return;
}