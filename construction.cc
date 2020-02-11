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

    Brique(Forme forme, Couleur couleur);
    ostream& afficher(ostream& sortie) const;
};

// Définitions de la classe Brique:
Brique::Brique(Forme forme, Couleur couleur)
        :forme(forme), couleur(couleur) { }

ostream& Brique::afficher(ostream& sortie) const {
    if (couleur == "")
        sortie << forme;
    else
        sortie << "(" << forme << ", " << couleur << ")";
    return sortie;
}

// Classe Construction
class Construction
{
    friend class Grader;

    // pour les tests lors des ajouts
    typedef vector<Brique> briques_k;
    typedef vector<briques_k> rangees_j;
    typedef vector<rangees_j> couches_i;

public:
    Construction(Brique brique);
    ostream& afficher(ostream& sortie) const;
    void operator^=(Construction const &c);
    void operator-=(Construction const &c);
    void operator+=(Construction const &b);
    // aides
    int Get_nb_couches_i() const;
    int Get_nb_rangees_j() const;
    int Get_nb_briques_k();
private:
    couches_i contenu;
};

// Définitions surcharges opérateurs internes
void Construction::operator^=(Construction const& c)
{
    int cpt_c(0);
    for (auto  couche : c.contenu) {
        contenu.push_back(c.contenu[cpt_c]);
        cpt_c++;
    }
}


void Construction::operator-=(Construction const& c)
{
    int cpt_c(0);
    int cpt_r(0);
        for (auto couche : c.contenu) {
            for (auto rangee : couche) {
                contenu.at(cpt_c).push_back(c.contenu.at(cpt_c).at(cpt_r));
                cpt_r++;
            }
            cpt_c++;
        }
}


//void Construction::operator-=(Construction const& c)
//{
//    int cpt_c(0);
//    int cpt_r(0);
//        for (auto couche : c.contenu) {
//            for (auto rangee : couche) {
//                contenu.at(cpt_c).push_back(c.contenu.at(cpt_c).at(cpt_r));
//                cpt_r++;
//            }
//            cpt_c++;
//        }
//}

void Construction::operator+=(Construction const& b)
{
    int cpt_c(0);
    int cpt_r(0);
    int cpt_b(0);
    if (b.Get_nb_couches_i() < Get_nb_couches_i()) {}
        else {
            if (b.Get_nb_rangees_j() < Get_nb_rangees_j()) {}
                else {
                    for (auto couche : b.contenu) {
                        for (auto rangee : couche) {
                            for (auto brique : rangee) {
                                contenu.at(cpt_c).at(cpt_r).push_back(b.contenu.at(cpt_c).at(cpt_r).at(cpt_b));
                                cpt_b++;
                            } cpt_r++;
                        } cpt_c++;
                    }
                }
    }
}



//void Construction::operator+=(Construction const& c)
//{
//    int cpt_c(0);
//    int cpt_r(0);
//    int cpt_b(0);
//
//    for (auto couche : c.contenu) {
//        for (auto rangee : couche) {
//            for (auto brique : rangee){
//                contenu.at(cpt_c).at(cpt_r).push_back(c.contenu.at(cpt_c).at(cpt_r).at(cpt_b));
//                cpt_b++;
//            }cpt_r++;
//        }cpt_c++;
//    }
//}


ostream &operator<<(ostream &out, const Brique &brique) {
    return brique.afficher(out);
}


// ^ Externe
const Construction operator^(Construction ca, Construction const &cb){
    ca ^= cb;
    return ca;
}

// ^ Externe
const Construction operator-(Construction ca, Construction const &cb){
    ca -= cb;
    return ca;
}

// ^ Externe
Construction operator+(Construction ca, Construction const &cb){
    ca += cb;
    return ca;
}

Construction::Construction(Brique brique)
        :contenu(1,vector<vector<Brique>>(1, vector<Brique> (1, brique))) { }


ostream& Construction::afficher(ostream& sortie) const
{
    int nb_etage(contenu.size()-1);
    for (auto it = contenu.rbegin(); it != contenu.rend(); it++){
        sortie << "Couche " << nb_etage << " :";
        nb_etage--; {
            for (auto const &profondeur : contenu[nb_etage+1]) {
                sortie << endl;
                for (auto const &largeur : profondeur) sortie << largeur << " ";
            }
            sortie << endl;
        }
    }
    return sortie;
}



// aide tmp
int Construction::Get_nb_couches_i() const
{
    int cpt(0);
    for (auto couches : contenu){
        cpt++;
    }
    return cpt;
}

// aide tmp
int Construction::Get_nb_rangees_j() const
{
    int cpt(0);
    for (auto couches : contenu){
        for (auto rangees : couches){
            cpt++;
        }
    }
    return cpt;
}

// aide tmp
int Construction::Get_nb_briques_k()
{
    int cpt(0);
    for (auto couches : contenu){
        for (auto rangees : couches){
            for (auto  briques : rangees)
                cpt++;
        }
    }
    return cpt;
}

ostream &operator<<(ostream &out, const Construction &construction) {
    return construction.afficher(out);
}

const Construction operator*(unsigned int n, Construction const &a)
{
    Brique br("","");
    Construction tmp(br);
    tmp=a;
    for (int i = 0; i<n-1; ++i) tmp += a;
    return tmp;
}

const Construction operator/(unsigned int n, Construction const &a)
{
    Brique br("","");
    Construction tmp(br);
    tmp=a;
    for (int i = 0; i<n-1; ++i) tmp ^= a;
    return tmp;
}

const Construction operator%(unsigned int n, Construction const &a)
{
    Brique br("","");
    Construction tmp(br);
    tmp=a;
    for (int i = 0; i<n-1; ++i) tmp -= a;
    return tmp;
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
