//
//  IFT1166, H24
//  TP2.Numero C
//
//  Auteur: Deanna Wung
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std; // librairie standard

class Personne {
private :
    char sexe ;
    float taille, poids ;
    int numero;

public :

    Personne(char sex, int num, float tail, float poid) {
        sexe = sex;
        numero = num;
        taille = tail;
        poids = poid;
    }
    
    // constructeur sans parametre dont le corps est VIDE
    Personne() {
    }
    
    int getNumero();
    char getSexe();
    float getTaille();
    float getPoids();
    
    void setNumero();
    void setSexe(char sexe);
    void setTaille(float taille);
    void setPoids(float poids);
    
    void afficher();

    // surcharge operateurs
    bool operator > (const Personne &autre);
    bool operator < (const Personne &autre);
    bool operator <= (const Personne &autre);
    bool operator > (int valeur) const;
    bool operator < (int valeur) const;

};


int Personne::getNumero(){
    return numero;
}

char Personne::getSexe(){
    return sexe;
}

float Personne::getTaille(){
    return taille;
}

float Personne::getPoids(){
    return poids;
}

void Personne::setSexe(char sexe){
    this->sexe = sexe;
}

void Personne::setPoids(float poids){
    this->poids = poids;
}

void Personne::setTaille(float taille){
    this->taille = taille;
}

void Personne::afficher(){
    cout << setw(8) << numero  << setw(8) << setprecision(2) << taille << setw(8) << poids << setw(8) << sexe << endl;
}

bool Personne::operator > (const Personne & autre){
    return this->numero > autre.numero;
}

bool Personne::operator < (const Personne & autre){
    return this->numero < autre.numero;
}

bool Personne::operator <= (const Personne & autre){
    return this->numero <= autre.numero;
}

bool Personne::operator < (int valeur) const{
    return this->numero < valeur;
}

bool Personne::operator > (int valeur) const{
    return this->numero > valeur;
}

/* lire tableau, instancier Personnes, compter nb de personnes et renvoyer par adresse */
void lireRemplir(const char nomALire[], Personne pers[], int & n) {
    const float PIED_EN_METRE = 0.3048,
    LIVRE_EN_KG = 0.454;
    int numero, nbPieds, nbPouces, nbLivres;
    float taille, poids;
    char sexe;
    
    ifstream  aLire (nomALire, ios::in); // localiser et ouvrir pour la lecture
    
    n = 0;
    while (aLire >> sexe >> numero >> nbPieds >> nbPouces >> nbLivres){
        taille = (nbPieds + nbPouces /12.0) * PIED_EN_METRE;
        poids  = nbLivres * LIVRE_EN_KG ;
        pers[n++] = Personne(sexe, numero, taille, poids);
    }
    aLire.close();
}

/*trouver la personne ayant le poids ou la taille minimale. prend un indicateur T ou P pour indiquer si
 on veut evaluer taille ou poids. renvoie personne mini par pointeur  */
void chercherPersMin(Personne tab[], int nbPers, char indiquertailleOuPoids, Personne *pMini){ // mettre un indicateur T ou P
    Personne personneMin = tab[0]; // initialiser 1ere personne
    for (int i=1; i < nbPers; i++) {
        
        float tailleOuPoidsPersonne;
        float tailleOuPoidsMin;
        
        if (indiquertailleOuPoids == 'T') {
            tailleOuPoidsPersonne = tab[i].getTaille();
            tailleOuPoidsMin = personneMin.getTaille();
        } else {
            tailleOuPoidsPersonne = tab[i].getPoids();
            tailleOuPoidsMin = tab[i].getPoids();
        }
        
        if(tailleOuPoidsPersonne < tailleOuPoidsMin){
            personneMin = tab[i];
        }
    }
    *pMini = personneMin;
}

/* chercher personne avec une valeur (taille ou poids) maximale. prends un indicateur M ou F pour indiquer sexe,
 prend un indicateur T ou P pour indiquer si on veut evaluer taille ou poids. renvoie personne maxi par pointeur */
void chercherHommeOuFemmePlusGrande(Personne tabPers[], int nbPers, char indiquerMOuF, char indiquerTailleOuPoids, Personne * pMaxi){
    Personne personneMaxi = tabPers[0];
    for (int i=0; i<nbPers; i++) {
        if (tabPers[i].getSexe() == indiquerMOuF) { // si c'est une femme (ou homme)
            float tailleOuPoidsPersonneMax;
            float tailleOuPoidsPersonneI;
            
            // chercher les valeurs en fonc si c'est T (taille) ou Poids
            if (indiquerTailleOuPoids == 'T') {
                tailleOuPoidsPersonneMax = personneMaxi.getTaille();
                tailleOuPoidsPersonneI = tabPers[i].getTaille();
            } else {
                tailleOuPoidsPersonneMax = personneMaxi.getPoids();
                tailleOuPoidsPersonneI = tabPers[i].getPoids();
            }
            
            if (tailleOuPoidsPersonneI > tailleOuPoidsPersonneMax) {
                // si plus grande que le max deja existant
                personneMaxi = tabPers[i];
            }
        }
    }
    * pMaxi = personneMaxi;
}

/* calculer la moyenne de taille ou de poids, de tou.t.e.s les hommes/femmes en prenant un indicateur M ou F, T ou P
renvoie resultat par pointeur  */
void calculerMoyenne(Personne tabPers[], int nbPers, char indiquerMOuF, char indiquerTailleOuPoids, float *moyen){
    float somme = 0.0;
    int compteur = 0;
    for (int i=0; i<nbPers; i++) {
        float valeurTailleOuPoids;
        if (indiquerTailleOuPoids == 'T') {
            valeurTailleOuPoids = tabPers[i].getTaille();
        } else {
            valeurTailleOuPoids = tabPers[i].getPoids();
        }
        
        if (tabPers[i].getSexe() == indiquerMOuF) {
            somme += valeurTailleOuPoids;
            compteur++;
        }
    }
    *moyen = somme / compteur;
}

/* afficher contenu d'un tableau de Personne, avec premiere ligne entete de libelles de chaque colonne */
void afficherTableau(Personne tabPers[], int nbPers){
    //entete
    cout << setw(8) << "numero"  << setw(8) << "taille" << setw(8) << "poids" << setw(8) << "sexe" << endl;

    //contenu
    for (int i=0; i<nbPers; i++) {
        tabPers[i].afficher();
    }
}

/* permuter la place de deux objets (on va utiliser pour permuter 2 Personnes) */
template <class T>
void permuter (T &a, T &b){
    T tempo = a;
    a = b;
    b = tempo;
}

/* fait partie de la methode quicksort, renvoie l'indice du pivot */
template <class T>
int partitionner (T tab[], int debut, int fin){
    int g = debut, d = fin;
    T pivot = tab[debut];
    
    do {
        while (g <= d && tab[g] <= pivot) g++;
        while (tab[d] > pivot) d--;
        
        if(g<d)
            permuter(tab[g], tab[d]);
    } while (g <= d);
    
    permuter(tab[d], tab[debut]);
    return d;
}

/* fonction quicksort (tri rapide) d'un tableau */
template <class T>
void quickSort(T tabPers[], int gauche, int droite){
    if (droite>gauche){
        int indPivot = partitionner(tabPers, gauche, droite);
        quickSort(tabPers, gauche, indPivot-1);
        quickSort(tabPers, indPivot+1, droite);
    }
}

/* recherche dichotomique d'un tableau d'objets.
 Ici, va etre utilisee pour rechercher une Personne ayant un certain numero mais fonction generique*/
template <class T>
int dicho(T tab[], int nbElem, T aChercher, T *trouvee){
    int mini = 0, maxi = nbElem-1;
    
    while(mini <= maxi){
        int milieu = (mini + maxi)/2;
        if(aChercher < tab[milieu])
            maxi = milieu - 1;
        else
            if(aChercher > tab[milieu])
                mini = milieu + 1;
            else {
                *trouvee = tab[milieu];
                return milieu;
            }
    }
    // si introuvable
    return -1;
}

/* effectuer et afficher les resultats d'une recherche dicho. montre introuvable si c'est le cas. 
 pour ne pas etre oblige d'ecrire ca 3 fois dans le main */
void dichoEtAfficher(Personne tabPers[], int nbPers, int numAChercher){
    Personne personneTrouvee;
    Personne aChercher = Personne('M', numAChercher, 0.0, 0.0); // instancier Personne avec numAChercher
    int indiceResultat = dicho(tabPers, nbPers, aChercher, &personneTrouvee);
    if (indiceResultat == -1)
        cout << "Numero " <<  numAChercher << " est introuvable!\n" << endl;
    else
        personneTrouvee.afficher();
}


int main() {
    // format affichage
    cout.setf(ios::fixed); cout.setf(ios::showpoint);
    
    //creer tableau
    const int MAX_PERS = 25 ;
    Personne pers[MAX_PERS];
    int nbPers;
    
    // lire fichier
    lireRemplir("imp_h24.txt",pers, nbPers);
    
    // 1. afficher le nombre de personnes lues
    cout << "1. afficher le nombre de personnes lues: \nOn a lu les infos de " << nbPers << " personnes\n";
    cout << "Le numero de la derniere personne : "
    << pers[nbPers-1].getNumero() << endl << endl;
    
    // 2. determiner et afficher les infos de la personne ayant la taille la plus petite
    cout << "2. Determiner et afficher la personne ayant la taille minimale " << endl;
    Personne personneMinTaille;
    chercherPersMin(pers, nbPers, 'T', &personneMinTaille);
    personneMinTaille.afficher();
    cout << endl;
    
    // 3. determiner et afficher les infos des personnes
    cout << "3. Afficher les infos des personnes... " << endl;
    cout << " a. la femme ayant la taille la plus grande" << endl;
    Personne femmeMaxTaille;
    chercherHommeOuFemmePlusGrande(pers, nbPers, 'F', 'T', &femmeMaxTaille);
    femmeMaxTaille.afficher();
    
    cout << " b. l'homme ayant le poids le plus lourd" << endl;
    Personne hommeMaxPoids;
    chercherHommeOuFemmePlusGrande(pers, nbPers, 'M', 'P', &hommeMaxPoids);
    hommeMaxPoids.afficher();
    cout << endl;
    
    // 4. calculer et afficher :
    cout << "4. Calculer et afficher :" << endl;
    float moyen = 0.0f;
    cout << " a. le poids moyen des hommes :" << endl;
    calculerMoyenne(pers, nbPers, 'M', 'P', &moyen);
    cout << moyen << endl << endl;
    
    cout << " b. la taille moyenne des femmes : " << endl;
    calculerMoyenne(pers, nbPers, 'F', 'T', &moyen);
    cout << moyen << endl << endl;
    
    // 5. trier (quicksort) les personnes selon leurs numeros et afficher le contenu du tableau pers apres le tri
    cout << "5. trier les personnes selon leurs numeros, puis afficher tableau" << endl;
    quickSort(pers, 0, nbPers-1);
    afficherTableau(pers, nbPers);
    cout << endl;

    // 6. rechercher et afficher les resultats de la recherche dichotomique ayant les numeros suivants
    cout << "recherche dichotomique des personnes ayant les numeros 2235, 2176, 9876 : " << endl;
    dichoEtAfficher(pers, nbPers, 2235);
    dichoEtAfficher(pers, nbPers, 2176);
    dichoEtAfficher(pers, nbPers, 9876);
    
    return 0;
    
}

/*
 
 Execution:
 
 1. afficher le nombre de personnes lues:
 On a lu les infos de 20 personnes
 Le numero de la derniere personne : 3498

 2. Determiner et afficher la personne ayant la taille minimale
     4433    1.47   57.66       M

 3. Afficher les infos des personnes...
  a. la femme ayant la taille la plus grande
     2176    1.88   84.90       F
  b. l'homme ayant le poids le plus lourd
     2879    1.88   86.71       M

 4. Calculer et afficher :
  a. le poids moyen des hommes :
 75.20

  b. la taille moyenne des femmes :
 1.72

 5. trier les personnes selon leurs numeros, puis afficher tableau
   numero  taille   poids    sexe
     1357    1.68   70.37       F
     2108    1.80   74.91       F
     2176    1.88   84.90       F
     2187    1.68   81.72       F
     2233    1.85   85.35       M
     2235    1.88   85.81       M
     2879    1.88   86.71       M
     3498    1.50   61.29       F
     4100    1.65   54.03       F
     4148    1.80   83.99       M
     4169    1.68   55.84       M
     4177    1.75   62.65       F
     4198    1.75   56.75       F
     4354    1.68   76.73       M
     4433    1.47   57.66       M
     4869    1.60   73.55       M
     5423    1.75   66.74       M
     5444    1.78   68.55       M
     5477    1.80   66.74       F
     5678    2.01   86.26       M

 recherche dichotomique des personnes ayant les numeros 2235, 2176, 9876 :
     2235    1.88   85.81       M
     2176    1.88   84.90       F
 Numero 9876 est introuvable!

 Program ended with exit code: 0
 
 */
