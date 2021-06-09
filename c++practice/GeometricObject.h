#include <functional>
class GeometricObject
{
private:
	double x, y;
public:
	GeometricObject() : x(0), y(0) {}
	GeometricObject(double x, double y) : x(x), y(y) {}
	double GetX() const { return x; }
	double GetY() const { return y; }
	void SetX(double nx) { x = nx; }
	void SetY(double ny) { y = ny; }
};

