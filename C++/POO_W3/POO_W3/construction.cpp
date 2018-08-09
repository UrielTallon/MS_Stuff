#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
	Brique(Forme f, Couleur c) : forme(f), couleur(c) {};

	ostream& afficher(ostream& sortie) const {
		if (couleur.compare("") == 0) {
			sortie << forme;
		}
		else {
			sortie << "(" << forme << ", " << couleur << ")";
		}
		return sortie;
	}
};

ostream& operator<<(ostream& os, const Brique& b) {
	return b.afficher(os);
}

class Construction
{
  friend class Grader;

private:
	vector<vector<vector<Brique>>> contenu;

public:
	Construction(Brique first) {
		vector<Brique> i;
		vector<vector<Brique>> j;
		i.push_back(first);
		j.push_back(i);
		contenu.push_back(j);
	}

	ostream&  afficher(ostream& sortie) const {
		for (int i(contenu.size() - 1); i >= 0; --i) {
			if (contenu[i].size() != 0) {
				sortie << "Couche " << i << " :" << endl;
				for (auto& deep : contenu[i]) {
					for (auto& len : deep) {
						len.afficher(sortie) << " ";
					}
					sortie << endl;
				}
			}
		}
		return sortie;
	}

	Construction& operator^=(const Construction& c) {
		for (auto new_const : c.contenu) {
			this->contenu.push_back(new_const);
		}
		return *this;
	}

	Construction& operator-=(const Construction& c) {
		if (c.contenu.size() >= this->contenu.size()) {
			for (size_t i(0); i < this->contenu.size(); ++i) {
				for (auto deep : c.contenu[i]) {
					this->contenu[i].push_back(deep);
				}
			}
		}
		return *this;
	}

	Construction& operator+=(const Construction& c) {
		if (c.contenu.size() >= this->contenu.size()) {
			for (size_t g(0); g < this->contenu.size(); ++g) {
				if (c.contenu[g].size() < this->contenu[g].size()) {
					return *this;
				}
			}
		}
		else {
			return *this;
		}

		for (size_t i(0); i < this->contenu.size(); ++i) {
			for (size_t j(0); j < this->contenu[i].size(); ++j) {
				for (auto br : c.contenu[i][j]) {
					this->contenu[i][j].push_back(br);
				}
			}
		}
		return *this;
	}
};

ostream& operator<<(ostream& os, const Construction& c) {
	return c.afficher(os);
}

const Construction operator^(Construction c1, Construction const& c2) {
	c1 ^= c2;
	return c1;
}

const Construction operator-(Construction c1, Construction const& c2) {
	c1 -= c2;
	return c1;
}

const Construction operator+(Construction c1, Construction const& c2) {
	c1 += c2;
	return c1;
}

const Construction operator*(unsigned int n, Construction const& a)
{
	Construction temp = a;
	for (size_t i(1); i < n; ++i) {
		temp += a;
	}
	return temp;
}

const Construction operator/(unsigned int n, Construction const& a)
{
	Construction temp = a;
	for (size_t i(1); i < n; ++i) {
		temp ^= a;
	}
	return temp;
}

const Construction operator%(unsigned int n, Construction const& a)
{
	Construction temp = a;
	for (size_t i(1); i < n; ++i) {
		temp -= a;
	}
	return temp;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  unsigned int largeur(4);
  unsigned int profondeur(3);
  unsigned int hauteur(3); // sans le toit

  // on construit les murs
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;

  return 0;
}
