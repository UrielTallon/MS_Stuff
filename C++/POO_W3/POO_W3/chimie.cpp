#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Flacon
{
private:
  string nom;
  double volume;
  double pH;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
#define BONUS
	Flacon(string n, double v, double p) : nom(n), volume(v), pH(p) {}

	ostream& etiquette(ostream& sortie) const {
		sortie << nom << " : " << volume << " ml, pH " << pH;
		return sortie;
	}

	Flacon& operator+=(const Flacon& f) {
		string new_name = nom + " + " + f.nom;
		double new_volume = volume + f.volume;
		double new_pH = volume * pow(10.0, -pH) + f.volume * pow(10.0, -f.pH);
		new_pH /= (volume + f.volume);
		new_pH = -log10(new_pH);
		this->nom = new_name;
		this->volume = new_volume;
		this->pH = new_pH;
		return *this;
	}
};

ostream& operator<<(ostream& os, const Flacon& f) {
	return f.etiquette(os);
}

Flacon operator+(Flacon f1, Flacon const f2) {
	f1 += f2;
	return f1;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void afficher_melange(Flacon const& f1, Flacon const& f2)
{
  cout << "Si je mélange " << endl;
  cout << "\t\"" << f1 << "\"" << endl;
  cout << "avec" << endl;
  cout << "\t\"" << f2 << "\"" << endl;
  cout << "j'obtiens :" << endl;
  cout << "\t\"" << (f1 + f2) << "\"" << endl;
}

int main_OLD()
{
  Flacon flacon1("Eau", 600.0, 7.0);
  Flacon flacon2("Acide chlorhydrique", 500.0, 2.0);
  Flacon flacon3("Acide perchlorique",  800.0, 1.5);

  afficher_melange(flacon1, flacon2);
  afficher_melange(flacon2, flacon3);

  return 0;

}
