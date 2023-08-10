/*******************************************************************
* 时间复杂度: O(1)
* 说明: 二维平面上一点绕另一点逆时针旋转
*******************************************************************/
const double PI = acos(-1);

inline double deg_to_rad(int x) { return x * PI / 180; }

struct Point
{
    double x, y;

    void rotate(double rad)
    {
        double newx = x * cos(rad) - y * sin(rad);
        double newy = x * sin(rad) + y * cos(rad);
        x = newx;
        y = newy;
        return;
    }

    void rotate(Point p, double rad)
    {
        Point rela = { x - p.x,y - p.y };
        rela.rotate(rad);
        x = rela.x + p.x;
        y = rela.y + p.y;
        return;
    }
};