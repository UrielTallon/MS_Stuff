#include <iostream>

using namespace std;

class Forme {
public:
	virtual void description() {
		cout << "Ceci est une forme !" << endl;
	}

	virtual double aire() = 0;
};

class Cercle : public Forme {
private:
	double rayon;
public:
	Cercle(double r) : rayon(r) {}

	void description() {
		cout << "Ceci est un cercle." << endl;
	}

	double aire() {
		return 3.14 * pow(rayon, 2);
	}
};

class Triangle : public Forme {
private:
	double base;
	double hauteur;
public:
	Triangle(double b, double h) : base(b), hauteur(h) {}

	void description() {
		cout << "Ceci est un triangle." << endl;
	}

	double aire() {
		return (base * hauteur) / 2.0;
	}
};

void affichageDesc(Forme& f) {
	f.description();
	cout << "Son aire est: " << f.aire() << endl;
}

int main_FORMES() {
	//Forme f;
	//Cercle c;
	//Forme f2(c);
	//affichageDesc(f);
	//affichageDesc(c);
	//f.description();
	//c.description();
	//f2.description();
	Cercle c(5);
	Triangle t(10, 2);
	affichageDesc(c);
	affichageDesc(t);
	return 0;
}