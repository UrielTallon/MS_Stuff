#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*****************************************************
  * Compléter le code à partir d'ici
 *****************************************************/
class Produit {
public:
	Produit(string n, string u = "") : nom(n), unit(u) {}
	string getNom() const { return nom; }
	string getUnite() const { return unit; }
	virtual string toString() const { return nom; }
	virtual const Produit* adapter() {
		return * this;
	}

protected:
	string nom;
	string unit;
};

class Ingredient {
public:
	Ingredient(const Produit& p, double q) : prod(p), quantite(q) {}
	Produit getProduit() const { return prod; }
	double getQuantite() const { return quantite; }
	void decriptionAdaptee() {
		cout << quantite << " " << prod.getUnite() << " de " << prod.toString();
	}

private:
	Produit prod;
	int quantite;
};

class Recette {
public:
	Recette(string n, double nb = 1.) : nom(n), nbFois_(nb) {}

	void ajouter(const Produit& p, double quantite) {
		ingredients.push_back(Ingredient(p, nbFois_ * quantite));
	}

	Recette adapter(double n) {
		Recette r(nom, n * nbFois_);
		for (Ingredient ing : ingredients) {
			r.ajouter(ing.getProduit(), n);
		}
		return r;
	}

	string toString() {
		ostringstream os;
		os << "Recette " << nom << " x " << nbFois_ << ":" << endl;
		for (size_t i(0); i < ingredients.size(); ++i) {
			os << i + 1 << ". " << ingredients[i].getProduit().getNom();
			if (i + 1 != ingredients.size()) {
				os << endl;
			}
		}
		return os.str();
	}

	double quantiteTotale(const string& nomProduit) const {
		return 0.0;
	}

private:
	string nom;
	double nbFois_;
	vector<Ingredient> ingredients;
};

class ProduitCuisine : public Produit {
public:
	ProduitCuisine(string n) : Produit(n, "portions(s)"), recette(n) {}
	
	void ajouterARecette(const Produit& produit, double quantite) {
		recette.ajouter(produit, quantite);
	}

	const ProduitCuisine* adapter(double n) {
		ProduitCuisine* pc(new ProduitCuisine(nom));
		pc->adapter(n);
		return pc;
	}

	string toString() {
		ostringstream os;
		os << Produit::toString() << endl;
		os << recette.toString();
		return os.str();
	}

private:
	Recette recette;
};



/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
{
  string nom = produit.getNom();
  cout << "Cette recette contient " << recette.quantiteTotale(nom)
       << " " << produit.getUnite() << " de " << nom << endl;
}

int main()
{
  // quelques produits de base
  Produit oeufs("oeufs");
  Produit farine("farine", "grammes");
  Produit beurre("beurre", "grammes");
  Produit sucreGlace("sucre glace", "grammes");
  Produit chocolatNoir("chocolat noir", "grammes");
  Produit amandesMoulues("amandes moulues", "grammes");
  Produit extraitAmandes("extrait d'amandes", "gouttes");

  ProduitCuisine glacage("glaçage au chocolat");
  // recette pour une portion de glaçage:
  glacage.ajouterARecette(chocolatNoir, 200);
  glacage.ajouterARecette(beurre, 25);
  glacage.ajouterARecette(sucreGlace, 100);
  cout << glacage.toString() << endl;

  ProduitCuisine glacageParfume("glaçage au chocolat parfumé");
  // besoin de 1 portions de glaçage au chocolat et de 2 gouttes
  // d'extrait d'amandes pour 1 portion de glaçage parfumé

  glacageParfume.ajouterARecette(extraitAmandes, 2);
  glacageParfume.ajouterARecette(glacage, 1);
  cout << glacageParfume.toString() << endl;

  Recette recette("tourte glacée au chocolat");
  recette.ajouter(oeufs, 5);
  recette.ajouter(farine, 150);
  recette.ajouter(beurre, 100);
  recette.ajouter(amandesMoulues, 50);
  recette.ajouter(glacageParfume, 2);

  cout << "===  Recette finale  =====" << endl;
  cout << recette.toString() << endl;
  afficherQuantiteTotale(recette, beurre);
  cout << endl;

  // double recette
  Recette doubleRecette = recette.adapter(2);
  cout << "===  Recette finale x 2 ===" << endl;
  cout << doubleRecette.toString() << endl;

  afficherQuantiteTotale(doubleRecette, beurre);
  afficherQuantiteTotale(doubleRecette, oeufs);
  afficherQuantiteTotale(doubleRecette, extraitAmandes);
  afficherQuantiteTotale(doubleRecette, glacage);
  cout << endl;

  cout << "===========================\n" << endl;
  cout << "Vérification que le glaçage n'a pas été modifié :\n";
  cout << glacage.toString() << endl;

  return 0;
}
