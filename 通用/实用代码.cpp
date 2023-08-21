//debug 常用宏
#define debug(x) cout << #x << " = " << x << endl

//本地文件读写
freopen("A.in", "r", stdin);
freopen("A.out", "w", stdout);

//builtin 系列位运算
__builtin_ffs(x); //最低位1是第几位（从1开始，不存在则0）
__builtin_clz(x)/__builtin_clzll(x); //前导高0的个数
__builtin_ctz(x)/__builtin_ctzll(x); //末尾低0的个数
__builtin_popcount(x); //1的个数
__builtin_parity(x); //1的个数的奇偶性

//最高位 1 的位置（从0开始，注意x不能为0）
__lg(x);

//long double 用浮点函数后面加l
sqrtl(x)/fabsl(x)/cosl(x);

// 随机数生成器（C++11，返回unsigned_int）
mt19937 mt(time(0));
mt();
shuffle(v.begin(), v.end(), mt);