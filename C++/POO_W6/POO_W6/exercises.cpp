#include <iostream>

using namespace std;

class Vehicle {
public:
	virtual void honk() = 0;
};

class Car : public Vehicle {
public:
	void honk() { cout << "Beep!"; }
};

class Boat : public Vehicle {
public:
	void honk() { cout << "Toot!"; }
};

class Hovercraft : public Car, public Boat {
public:
	using Car::honk;
};

class Figure {
public:
	Figure() { cout << "F"; }
};

class Line : virtual public Figure {
private:
	double length;

public:
	Line(double l) : length(l) { cout << "L"; }
};

class Square : virtual public Figure{
private:
	double side;

public:
	Square(double s) : side(s) { cout << "S"; }
};

class Parallelepiped : public Square, public Line {
public:
	Parallelepiped(double base, double height) : Line(height), Square(base) { cout << "P"; }
};

int main_EXO() {
	Hovercraft h;
	h.Car::honk();
	h.honk();

	Car* c(new Hovercraft());
	c->honk();
	delete c;

	Parallelepiped p(1, 2);

	return 0;
}