#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
// Chaines de caractères à utiliser pour les affichages:
/*

été jeté

d'un

n'est

L'oeuvre

bibliothèque

détruit

*/
class Auteur {
private:
	string nom;
	bool award;

	Auteur(const Auteur& auteur);

public:
	Auteur(string n, bool a = false): nom(n), award(a) {

	}

	~Auteur() {

	}
	
	string getNom() const {
		return nom;
	}

	bool getPrix() const {
		return award;
	}
};

class Oeuvre {
private:
	string titre;
	const Auteur& auteur;
	string langue;

	Oeuvre(const Oeuvre& oeuvre);

public:
	Oeuvre(string t, const Auteur& a, string l): titre(t), auteur(a), langue(l) {

	}

	~Oeuvre() {
		cout << "L'Oeuvre \"" << titre << ", " << auteur.getNom() << ", en " << langue
			<< "\" n'est plus disponible."<< endl;
	}

	string getTitre() const {
		return titre;
	}

	const Auteur& getAuteur() const {
		return auteur;
	}

	string getLangue() const {
		return langue;
	}

	void affiche() {
		cout << titre << ", " << auteur.getNom() << ", en " << langue << endl;
	}
};

class Exemplaire {
private:
	Oeuvre& oeuvre;

public:

	Exemplaire(Oeuvre& e) : oeuvre(e) {
		cout << "Nouvel exemplaire de : " << oeuvre.getTitre() << ", " <<
			oeuvre.getAuteur().getNom() << ", en " << oeuvre.getLangue() << endl;
	}

	Exemplaire(const Exemplaire& ex): oeuvre(ex.getOeuvre()) {
		cout << "Copie d'un exemplaire de : " << oeuvre.getTitre() << ", " <<
			oeuvre.getAuteur().getNom() << ", en " << oeuvre.getLangue() << endl;
	}

	~Exemplaire() {
		cout << "Un exemplaire de \"" << oeuvre.getTitre() << ", " << oeuvre.getAuteur().getNom()
			<< ", en " << oeuvre.getLangue() << "\" a été jeté !" << endl;
	}

	Oeuvre& getOeuvre() const {
		return oeuvre;
	}

	void affiche() {
		cout << "Exemplaire de : " << oeuvre.getTitre() << ", " << oeuvre.getAuteur().getNom()
			<< ", en " << oeuvre.getLangue();
	}
};

class Bibliotheque {
private:
	string nom;
	vector<Exemplaire*> stock;

public:

	Bibliotheque(string n) : nom(n) {
		cout << "La bibliothèque " << nom << " est ouverte !" << endl;
	}

	~Bibliotheque() {
		cout << "La bibliothèque " << nom << " ferme ses portes, " << endl 
			<< "et détruit ses exemplaires : " << endl;
		for (Exemplaire* ex : stock) {
			delete ex;
		}
	}

	string getNom() {
		return nom;
	}

	void stocker(Oeuvre& e, unsigned int n = 1) {
		for (size_t i(0); i < n; ++i) {
			stock.push_back(new Exemplaire(e));
		}
	}

	void lister_exemplaires(string l = "") {
		if (l.compare("") == 0) {
			for (Exemplaire* ex : stock) {
				ex->affiche();
				cout << endl;
			}
		}
		else {
			for (Exemplaire* ex : stock) {
				if (ex->getOeuvre().getLangue().compare(l) == 0) {
					ex->affiche();
					cout << endl;
				}
			}
		}
	}

	int compter_exemplaires(Oeuvre& e) const {
		int compteur(0);
		for (Exemplaire* ex : stock) {
			if (ex->getOeuvre().getAuteur().getNom() == e.getAuteur().getNom() &&
				ex->getOeuvre().getTitre() == e.getTitre() &&
				ex->getOeuvre().getLangue() == e.getLangue() &&
				ex->getOeuvre().getAuteur().getPrix() == e.getAuteur().getPrix()) {
				++compteur;
			}
		}
		return compteur;
	}

	void afficher_auteurs(bool award = false) {
		if (award) {
			for (Exemplaire* ex : stock) {
				if (ex->getOeuvre().getAuteur().getPrix()) {
					cout << ex->getOeuvre().getAuteur().getNom() << endl;
				}
			}
		}
		else {
			for (Exemplaire* ex : stock) {
				cout << ex->getOeuvre().getAuteur().getNom() << endl;
			}
		}
	}
};
/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
         o2("L'Homme qui rit"          , a1, "français" ),
         o3("Le Comte de Monte-Cristo" , a2, "français" ),
         o4("Zazie dans le métro"      , a3, "français" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothèque " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  const string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs à succès sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}
