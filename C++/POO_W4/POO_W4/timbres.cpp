#include <iostream>
#include <string>
using namespace std;

class Timbre
{
private:
  static constexpr unsigned int ANNEE_COURANTE = 2016;

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
	string nom;
	unsigned int annee;
	string pays;
	double valeur_faciale;

public:
	Timbre(string n, unsigned int a, string p = "Suisse", double v = 1.0) : 
		nom(n), annee(a), pays(p), valeur_faciale(v) {}

	double vente() {
		if (age() < 5) {
			return valeur_faciale;
		}
		else {
			return valeur_faciale * 2.5 * age();
		}
	}

	unsigned int age() {
		return ANNEE_COURANTE - annee;
	}

	// virtual to enable polymorphism
	virtual ostream& afficher(ostream& os) const {
		os << "de nom " << nom << " datant de " << annee << " (provenance " << pays <<
			") ayant pour valeur faciale " << valeur_faciale << " francs";
		return os;
	}
 
};

class Rare : public Timbre {
private:
	static constexpr unsigned int PRIX_BASE_TRES_RARE = 600;
	static constexpr unsigned int PRIX_BASE_RARE = 400;
	static constexpr unsigned int PRIX_BASE_PEU_RARE = 50;
	const int exemplaires;

public:
	Rare(string n, unsigned int a, string p = "Suisse", double v = 1.0, int e = 100) : 
	Timbre(n, a, p, v), exemplaires(e) {}

	int nb_exemplaires() const {
		return exemplaires;
	}
	
	double vente() {
		double base;
		if (exemplaires < 100) {
			base = PRIX_BASE_TRES_RARE;
		}
		else if (exemplaires >= 100 && exemplaires < 1000) {
			base = PRIX_BASE_RARE;
		}
		else {
			base = PRIX_BASE_PEU_RARE;
		}
		return base * (age() / 10.0);
	}

	ostream& afficher(ostream& os) const {
		os << "rare (" << exemplaires << " ex.) ";
		return Timbre::afficher(os);
	}
};

class Commemoratif : public Timbre {
public:
	Commemoratif(string n, unsigned int a, string p = "Suisse", double v = 1.0) : 
	Timbre(n, a, p, v) {}

	double vente() {
		return Timbre::vente() * 2;
	}

	ostream& afficher(ostream& os) const {
		os << "commémoratif ";
		return Timbre::afficher(os);
	}
};

// Timbre must be passed by reference so as to authorize dynamic link resolution
ostream& operator<<(ostream& os, const Timbre& t) {
	os << "Timbre ";
	return t.afficher(os);
}

/*
ostream& operator<<(ostream& os, const Timbre t) {
	os << "Timbre ";
	return t.afficher(os);
}

ostream& operator<<(ostream& os, const Rare t) {
	os << "Timbre rare (" << t.nb_exemplaires() << " ex.) ";
	return t.afficher(os);
}

ostream& operator<<(ostream& os, const Commemoratif t) {
	os << "Timbre commémoratif ";
	return t.afficher(os);
}
*/

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main_OLD2()
{
  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Rare t1( "Guarana-4574", 1960, "Mexique", 0.2, 98 );
  Rare t2( "Yoddle-201"  , 1916, "Suisse" , 0.8,  3 );

  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Commemoratif t3( "700eme-501"  , 2002, "Suisse", 1.5 );
  Timbre       t4( "Setchuan-302", 2004, "Chine" , 0.2 );

  /* Nous n'avons pas encore le polymorphisme :-(
   * (=> pas moyen de faire sans copie ici :-( )  */
  cout << t1 << endl;
  cout << "Prix vente : " << t1.vente() << " francs" << endl;
  cout << t2 << endl;
  cout << "Prix vente : " << t2.vente() << " francs" << endl;
  cout << t3 << endl;
  cout << "Prix vente : " << t3.vente() << " francs" << endl;
  cout << t4 << endl;
  cout << "Prix vente : " << t4.vente() << " francs" << endl;

  return 0;
}
