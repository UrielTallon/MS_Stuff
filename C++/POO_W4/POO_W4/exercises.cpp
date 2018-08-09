#include <iostream>

class Rect {
private:
	double width, height;
public:
	double getWidth() const {
		return width;
	}
	double getHeight() const {
		return height;
	}
};

class ColoredRect : public Rect {
protected:
	int color;
	void init();
public:
	double getSurface() const {
		return getWidth() * getHeight();
	}

	int getColor() const {
		return color;
	}
};

class Square {
private:
	double size;
public:
	double surface() {
		return size * size;
	}
	double getEdge() {
		return size;
	}
};

class Cube : public Square {
public:
	double surface() {
		return 6 * Square::surface();
	}
};

class Rector {
public:
	Rector() { std::cout << "1"; }
	~Rector() { std::cout << "2"; }
};

class Rector2 : protected Rector {
public:
	Rector2() { std::cout << "3"; }
	~Rector2() { std::cout << "4"; }
};

class Test {
public:
	static void op_static() {
		std::cout << "HERE" << std::endl;
	}
	void op() {
		std::cout << "AND ALSO HERE" << std::endl;
	}
};

class A {
private:
	int a;
public:
	A(int a1) : a(a1) {}
	int getA() const { return a; }
	//virtual void test() = 0;
	virtual void disp() const { std::cout << "a"; }
	virtual void print() const { std::cout << "A"; }
};

class B: public A {
private:
	int b;
public:
	B(int a1, int b1) : A(a1), b(b1) {}
	int getB() const { return b; }
	//void test() override { std::cout << "test"; }
	void disp() const override { std::cout << "b"; }
	void print() const { std::cout << "B"; }
};

void operate1(A in) { std::cout << in.getA(); }
void operate2(B in) { std::cout << in.getB(); }

//void display(A* in) { in->print(); } B
//void display(A& in) { in.print(); } B
//void display(A const& in) { in.print(); } B
void display(B in) { in.print(); }
//void display(A in) { in->print(); } error
//void display(A** in) { in->print(); } error
//void display(B* in) { in.print(); } error
//void display(A in) { in.print(); }

int main() {
	//Test t;

	//Test::op_static();
	A a(1);
	B b(2, 42);
	A c(b);

	B* t = &b;
	A* y = &b;


	//display(a);
	display(b);

}