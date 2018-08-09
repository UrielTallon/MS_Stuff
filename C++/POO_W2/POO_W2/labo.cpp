#include <iostream>
#include <string>
using namespace std;

class Souris
{
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
private:
	double poids;
	string couleur;
	unsigned int age;
	unsigned int esperance_vie;
	bool clonee;

public:
	Souris(double p, string c, unsigned int a = 0, unsigned int v = 36): 
		poids(p), couleur(c), age(a), esperance_vie(v) {
		clonee = false;
		cout << "Une nouvelle souris !" << endl;
	}

	Souris(const Souris &souris):
		poids(souris.poids), couleur(souris.couleur), age(souris.age), esperance_vie(souris.esperance_vie) {
		clonee = true;
		double temp = (4.0 / 5.0) * double(esperance_vie);
		esperance_vie = temp;
		cout << "Clonage d'une souris !" << endl;
	}

	~Souris() {
		cout << "Fin d'une souris..." << endl;
	}

	void afficher() const {
		if (!clonee) {
			cout << "Une souris " << couleur << " de " << age << " mois et pesant " << 
				poids << " grammes" << endl;
		}
		else {
			cout << "Une souris " << couleur << ", clonee, de " << age << " mois et pesant " <<
				poids << " grammes" << endl;
		}
	}

	void vieillir() {
		++age;
		if (age > (esperance_vie / 2) && clonee) {
			couleur = "verte";
		}
	}

	void evolue() {
		for (int y(age); y < esperance_vie; ++y) {
			this->vieillir();
		}
	}
  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

}; // fin de la classe Souris

int main_NO()
{
  Souris s1(50.0, "blanche", 2);
  Souris s2(45.0, "grise");
  Souris s3(s2);
  // ... un tableau peut-être...
  s1.afficher();
  s2.afficher();
  s3.afficher();
  s1.evolue();
  s2.evolue();
  s3.evolue();
  s1.afficher();
  s2.afficher();
  s3.afficher();
  return 0;
}
