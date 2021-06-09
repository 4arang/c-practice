#include <functional>
const double PI = 3.141592;
class Circle2D
{
	double mX;
	double mY;
	double mRadius;

private:
	double GetLength(const double x,const double y) const
	{
		double dx = mX - x;
		double dy = mY - y;
		return sqrt(dx * dx + dy * dy);
	}
public:
	Circle2D() : mX(0), mY(0), mRadius(1) {}
	Circle2D( double x, double y, double r): mX(x), mY(y), mRadius(r) {}
	double GetX() const { return mX; }
	double GetY() const { return mY; }
	double GetRadius() const { return mRadius; }
	double GetArea() const { return PI * mRadius * mRadius; }
	double GetPerimeter() const { return 2 * PI * mRadius; }
	bool Contains(double x, double y)const { return mRadius >= GetLength(x, y); }
	bool Contains(const Circle2D& circle) const 
	{
		return mRadius - circle.GetRadius() >= GetLength(circle.GetX(), circle.GetY());
	}
	bool overlaps(const Circle2D & circle) const
	{
		return mRadius > GetLength(circle.GetX(), circle.GetY());
	}
};

