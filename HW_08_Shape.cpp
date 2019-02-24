#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

#define PI 3.14159265


class Shape {
public:
	virtual double GetArea() = 0;
	virtual void Draw() = 0;
	virtual ~Shape() {}
};


class Point : public Shape {
	double x_ = 0;
	double y_ = 0;
public:
	Point() {}
	Point(const double x, const double y) :
		x_(x),
		y_(y)
	{}
	Point(const Point& obj) :
		x_(obj.x_),
		y_(obj.y_)
	{};
	double getX() const {
		return x_;
	}
	double getY() const {
		return y_;
	}
	double GetArea() {
		return 0;
	}
	void Draw() {
		std::cout << "[ " << x_ << "; " << y_ << " ]";
	}
	~Point() {}
};


class Triangle : public Shape {
	Point p1_;
	Point p2_;
	Point p3_;
public:
	Triangle() {}
	Triangle(const Point& p1, const Point& p2, const Point& p3) :
		p1_(p1),
		p2_(p2),
		p3_(p3)
	{}
	double GetArea() {
		return (abs((p2_.getX() - p1_.getX()) * (p3_.getY() - p1_.getY()) -
			(p3_.getX() - p1_.getX()) * (p2_.getY() - p1_.getX())) / 2);
	}
	void Draw() {
		std::cout << "Triangle: ( ";
		p1_.Draw();
		std::cout << "; ";
		p2_.Draw();
		std::cout << "; ";
		p3_.Draw();
		std::cout << " )" << std::endl;
	}
	~Triangle() {}
};


class Square : public Shape {
	double side_;
public:
	Square() {}
	Square(double side) :
		side_(side)
	{}
	Square(const Point& p1, const Point& p2) :
		side_(abs(p2.getX() - p1.getX()))
	{}
	double GetArea() {
		return pow(side_, 2);
	}
	void Draw() {
		std::cout << "Square: ( " << side_ << " )" << std::endl;
	}
	~Square() {}
};


class Rectangle : public Shape {
	Point p1_;
	Point p2_;
public:
	Rectangle() {}
	Rectangle(const Point& p1, const Point& p2) :
		p1_(p1),
		p2_(p2)
	{}
	Rectangle(const Rectangle& obj) :
		p1_(obj.p1_),
		p2_(obj.p2_)
	{};
	Point getP1() {
		return p1_;
	}
	Point getP2() {
		return p2_;
	}
	double getSide1() {
		return abs(p2_.getX() - p1_.getX());
	}
	double getSide2() {
		return abs(p1_.getY() - p2_.getY());
	}
	double GetArea() {
		return getSide1() * getSide2();
	}
	void Draw() {
		std::cout << "Rectangle: ( ";
		p1_.Draw();
		std::cout << "; ";
		p2_.Draw();
		std::cout << " )" << std::endl;
	}
	~Rectangle() {}
};


class Ellipse : public Shape {
	Point centre_;
	double radius1_;
	double radius2_;
public:
	Ellipse() {}
	Ellipse(const Point& centre, const double radius1, const double radius2) :
		centre_(centre),
		radius1_(radius1),
		radius2_(radius2)
	{}
	Ellipse(const Point& centre, const Point& circleOx, const Point& circleOy) :
		centre_(centre),
		radius1_(abs(circleOx.getX() - centre.getX())),
		radius2_(abs(circleOy.getY() - centre.getY()))
	{}
	double GetArea() {
		return PI * radius1_ * radius2_;
	}
	void Draw() {
		std::cout << "Ellipse: ( ";
		centre_.Draw();
		std::cout << "; " << radius1_ << "; " << radius2_ << " )" << std::endl;
	}
	~Ellipse() {}
};


class Ellipse1 : public Shape {
	Rectangle rec_;
public:
	Ellipse1() {}
	Ellipse1(const Rectangle& rec) :
		rec_(rec)
	{}
	double getRadiusOx() {
		return rec_.getSide1() / 2;
	}
	double getRadiusOy() {
		return rec_.getSide2() / 2;
	}
	double GetArea() {
		return PI * getRadiusOx() * getRadiusOy();
	}
	void Draw() {
		std::cout << "Ellipse: ( ";
		rec_.getP1().Draw();
		std::cout << "; ";
		rec_.getP2().Draw();
		std::cout << " )" << std::endl;
	}
	~Ellipse1() {}
};


class Circle : public Shape {
	Point centre_;
	Point circle_;
public:
	Circle() {}
	Circle(const Point& centre, const Point& circle) :
		centre_(centre),
		circle_(circle)
	{}
	double getRadius() {
		return sqrt(pow((circle_.getY() - centre_.getY()), 2) +
			pow((circle_.getX() - centre_.getX()), 2));
	}
	double GetArea() {
		return PI * ((pow(getRadius(), 2)));
	}
	void Draw() {
		std::cout << "Circle: ( ";
		centre_.Draw();
		std::cout << "; ";
		circle_.Draw();
		std::cout << " )" << std::endl;
	}
	~Circle() {}
};


void DrawShapes(std::vector<std::unique_ptr<Shape>>& shapes) {
	for (auto & a : shapes) {
		a->Draw();
	}
}


double GetShapesArea(std::vector<std::unique_ptr<Shape>>& shapes) {
	double area = 0;
	for (auto & a : shapes) {
		area += a->GetArea();
	}
	return area;
}


int main() {

	std::vector<std::unique_ptr<Shape>> v;
	
	v.push_back(std::make_unique<Triangle>(Point(1, 1), Point(1, 4), Point(3, 3)));
	v.push_back(std::make_unique<Rectangle>(Point(1, 1), Point(2, 3)));
	v.push_back(std::make_unique<Circle>(Point(1, 1), Point(3, 3)));
	v.push_back(std::make_unique<Ellipse>(Point(0, 0), 2, 4));
	v.push_back(std::make_unique<Square>(3));
	v.push_back(std::make_unique<Ellipse1>(Rectangle(Point(-2, 4), Point(2, -4))));

	std::cout << "Count of shapes: " << v.size() << std::endl;

	DrawShapes(v);

	std::cout << "Area: " << std::endl;
	for (auto& a : v) {
		std::cout << a->GetArea() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Summary area: " << GetShapesArea(v) << std::endl;
	std::cout << std::endl;

	system("pause");
	return 0;
}
