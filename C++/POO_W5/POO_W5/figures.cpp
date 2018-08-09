#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Figure {
public:
	virtual ~Figure() {
		cout << "Une figure de moins." << endl;
	}

	virtual void affiche() const = 0;
	virtual Figure* copie() const = 0;
	virtual unique_ptr<Figure> copie_b() const = 0;
};

class Cercle : public Figure {
private:
	double rayon;

public:
	Cercle(double r = 0.0): rayon(r) {
		cout << "Construction d'un cercle de rayon " << rayon << endl;
	}

	Cercle(const Cercle& c): Figure(c), rayon(c.rayon) {
		cout << "Copie d'un cercle de rayon " << rayon << endl;
	}

	~Cercle() {
		cout << "Destruction d'un cercle" << endl;
	}

	void affiche() const override {
		cout << "Cercle de rayon " << rayon << endl;
	}

	Figure* copie() const { return new Cercle(*this); }
	
	unique_ptr<Figure> copie_b() const override {
		return unique_ptr<Figure>(new Cercle(*this));
	}
};

class Carre :public Figure {
private:
	double cote;

public:
	Carre(double c = 0.0): cote(c) {
		cout << "Construction d'un carre de cote " << cote << endl;
	}
	
	Carre(const Carre& c) : Figure(c), cote(c.cote) {
		cout << "Copie d'un carre de cote " << cote << endl;
	}

	~Carre() {
		cout << "Destruction d'un carre" << endl;
	}

	void affiche() const override {
		cout << "Carre de cote " << cote << endl;
	}

	Figure* copie() const { return new Carre(*this); }

	unique_ptr<Figure> copie_b() const override {
		return unique_ptr<Figure>(new Carre(*this));
	}
};

class Triangle :public Figure {
private:
	double base;
	double hauteur;

public:
	Triangle(double b = 0.0, double h = 0.0): base(b), hauteur(h) {
		cout << "Construction d'un triangle de base " << base << " et de hauteur " << hauteur << endl;
	}

	Triangle(const Triangle& t) : Figure(t), base(t.base), hauteur(t.hauteur) {
		cout << "Copie d'un triangle de base " << base << " et de hauteur " << hauteur << endl;
	}

	~Triangle() {
		cout << "Destruction d'un triangle" << endl;
	}

	void affiche() const override {
		cout << "Triangle de base " << base << " et de hauteur " << hauteur << endl;
	}

	Figure* copie() const { return new Triangle(*this); }

	unique_ptr<Figure> copie_b() const override {
		return unique_ptr<Figure>(new Triangle(*this));
	}
};

class Dessin {
private:
	vector<Figure*> contenu;
	vector<unique_ptr<Figure>> contenu_b;

public:
	~Dessin() {
		cout << "Le dessin s'efface..." << endl;
		for (size_t i(0); i < contenu.size(); ++i) {
			delete contenu[i];
		}
	}

	void ajouteFigure(Figure& const fig) {
		contenu.push_back(fig.copie());
		contenu_b.push_back(fig.copie_b());
	}

	void affiche() const {
		cout << "Contenu: " << endl;
		for (Figure* f : contenu) {
			f->affiche();
		}
	}
};

void unCercleDePlus(Dessin const& img) {
	Dessin tmp(img);
	tmp.ajouteFigure(Cercle(1));
	cout << "Affichage de 'tmp' : " << endl;
	tmp.affiche();
}

int main() {
	Dessin dessin;

	dessin.ajouteFigure(Triangle(3, 4));
	dessin.ajouteFigure(Carre(2));
	dessin.ajouteFigure(Triangle(6, 1));
	dessin.ajouteFigure(Cercle(12));
	
	unCercleDePlus(dessin);
	
	cout << endl << "Affichage du dessin : " << endl;
	dessin.affiche();
	return 0;
}