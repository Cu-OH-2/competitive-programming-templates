/*******************************************************************
* 时间复杂度: O(1)
* 说明: 二维平面上三点坐标叉乘求三角形面积
*******************************************************************/
struct Point
{
    double x, y;
};

double area(const Point& p1, const Point& p2, const Point& p3)
{
    return fabs((p2.y - p1.y) * (p3.x - p1.x) - (p3.y - p1.y) * (p2.x - p1.x)) / 2;
}