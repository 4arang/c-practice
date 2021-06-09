#include <functional>
#include "Circle.h"
#include "Rectangle2D.h"
class MyPoint
{
	double x, y;
public:
	MyPoint() : x(0), y(0) {}
	MyPoint(double x, double y) : x(x), y(y) {}
	double GetX() const { return x; }
	double GetY() const { return y; }
	double GetDistance(const MyPoint & point) const
	{
		double dx = x - point.x;
		double dy = y - point.y;
		return sqrt(dx * dx + dy * dy);
	}
	bool IsIn(const Circle2D& circle) { return circle.Contains(x, y); }
	bool IsIn(const Rectangle2D& rect) { return rect.Contains(x, y); }
};
