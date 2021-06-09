#include <functional>
class Rectangle2D
{
	double x, y, width, height;
public:
	Rectangle2D() : x(0), y(0), width(1), height(1) {}
	Rectangle2D(double x, double y, double w, double h) : x(x), y(y), width(w), height(h) {}
	double GetX() const { return x; }
	double GetY() const { return y; }
	double GetH() const { return height; }
	double GetW() const { return width; }
	double GetArea() const { return width * height; }
	double GetPerimeter() const { return 2 * (width + height); }
	bool Contains(double nx, double ny) const { return abs(x - nx) <= width && abs(y - ny) <= height; }
	bool Contains(const Rectangle2D& other) const
	{
		return x <= other.x && x + width <= other.x + other.width
			&& y <= other.y && y + height >= other.y + other.height;
	}
	bool Overlaps(const Rectangle2D & other) const
	{
		return x <= other.x && x + width >= other.x
			&& y <= other.y && y + height >= other.y;
	}
};

