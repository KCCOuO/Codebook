struct point {
    double x, y;
    point(double x = 0, double y = 0) : x(x), y(y) {}
    point operator - (const point& b) const { return point(x - b.x, y - b.y); }
    point operator + (const point& b) const { return point(x + b.x, y + b.y); }
    point operator * (double k) const { return point(x * k, y * k); }
};
double cross(point a, point b) {return a.x * b.y - a.y * b.x;}
// 直線ab與直線cd的交點
point intersect(point a, point b, point c, point d)
{
    double c1 = cross(b - a, c - a);
    double c2 = cross(b - a, d - a);
    return c + (d - c) * (c1 / (c1 - c2));
}