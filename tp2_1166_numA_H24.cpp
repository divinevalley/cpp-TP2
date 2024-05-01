//  TP2.
//  Numero A.
//  IFT 1166, H24
//  Auteur: Deanna Wung
//

#include <iostream>
#include <iomanip>
using namespace std;

/* pour a. convertit un numero de telephone au format xxxxxxxxxx
en format (xxx) xxx-xxxx */
string convertirFormat(string numero){
    return "(" + numero.substr(0,3) + ") " + numero.substr(3,3) + "-" + numero.substr(6,4);
}

/* afficher un numero de telephone depuis son format brut xxxxxxxxxx
 et avec son nom par exemple :
 Le telephone de Jean :   (450) 123-4567 */
void afficher(string numeroBrut, string prefixe){
    cout << prefixe << " : " << setw(3) << convertirFormat(numeroBrut) << endl;
}

/* compter le nombre de fois un chiffre donne apparait dans un numero de telephone donne */
int compterOccurences(string numeroTel, string aCompter){
    int compteur = 0; // initialiser
    for (int i=0; i<numeroTel.length(); i++) { // parcourir numeroTel
        if (aCompter.find(numeroTel[i]) != string::npos){ // si trouve
            compteur++;
        }
    }
    return compteur;
}

/* pour b.
 compter les occurences d'un certain chiffre dans un numero de telephone donne,
 et afficher le resultat sous format demande ("il y a x fois le caractere...") */
void afficherCompte(string numeroTel, string aCompter, string nomPersonne){
    int occurences = compterOccurences(numeroTel, aCompter);
    cout << "Il y a " << occurences << " fois le caractere chiffre '" 
    << aCompter << "' dans le numero de telephone de " << nomPersonne << endl;
}

/* pour c. renvoie true si tout les caracteres chiffres du numero A figurent
dans numero B */
bool numAFigureDansNumB(string numeroA, string numeroB){
    for (int i=0; i<numeroA.length(); i++) { // parcourir numero A
        if (numeroB.find(numeroA[i]) == string::npos) { // si jamais 1 fois, c'est introuve,
            return false; // c'est false et termine
        }
    }
    // seulement si on a tout parcouru et survecu jusqu'ici, c'est true
    return true;
}

/* pour d. afficher les numeros dans numeroA qui
 ne sont pas dans numeroB */
void afficherNumsDansAPasDansB(string numeroA, string numeroB){
    // parcourir numero A
    // si pas present dans B, afficher
    
    for (int i=0; i < numeroA.length(); i++) {
        if (numeroB.find(numeroA[i]) == string::npos) { // si introuve
            // afficher
            cout << numeroA[i] << " ";
        }
    }
    cout << endl << endl;
}

/* pour e.-f. afficher les numeros pairs ou impairs dans l'ordre
 sans doublon d'un certain num de telephone */
void afficherNumsPairsOuImpairs(string tel, string pairOuImpair){
    // parcourir string pairOuImpair (ie. 02468)
    for (int i = 0; i<pairOuImpair.length(); i++) {
        
        // si present, afficher
        if(tel.find(pairOuImpair[i])!= string::npos){ // si trouve,
            // afficher
            cout << pairOuImpair[i] << " ";
        }
    }
    cout << endl << endl;
}

/* pour g. determiner et afficher le plus grand caractere chiffre
 d'un certain numero donne */
void afficherMax(string numero, string nomPersonne){
    int max = -1; // initialiser

    for (int i=0; i<numero.length(); i++) {
        int numeroIConverti = numero[i] - '0';
        if (numeroIConverti > max){
            max = numeroIConverti; // mettre a jour max
        }
    }
    // une fois tout parcouru, afficher max
    cout << "Le plus grand chiffre du numero de telephone de "
    << nomPersonne << " : " << max << endl << endl;
}

/* pour g. determiner et afficher le plus petit caractere chiffre
 d'un certain numero donne */
void afficherMin(string numero, string nomPersonne){
    int min = 99; // initialiser

    for (int i=0; i<numero.length(); i++) {
        int numeroIConverti = numero[i] - '0';
        if (numeroIConverti < min){
            min = numeroIConverti; // mettre a jour min
        }
    }
    // une fois tout parcouru, afficher max
    cout << "Le plus petit chiffre du numero de telephone de "
    << nomPersonne << " : " << min << endl << endl;
}

int main(int argc, const char * argv[]) {
    
    string telUdM = "5143436111", telJean = "4501234567";
    
    // a) extraire avec des sous chaines appropriees puis afficher à l'ecran
    cout << " a) " << endl;
    afficher(telUdM, "Le telephone de l'Universite de Montreal");
    afficher(telJean, "Le telephone de Jean");
    cout << endl;
    
    // b) compter et afficher
    cout << " b) " << endl;
    afficherCompte(telUdM, "4", "UdeM");
    afficherCompte(telUdM, "1", "UdeM");
    afficherCompte(telJean, "7", "Jean");
    cout << endl;
    
    // c) prouver, par fonction bool, que tous les caracteres chiffres du
    // numero de tel UdeM figurent dans celui de Jean
    cout << " c) " << endl;
    if (numAFigureDansNumB(telUdM, telJean)){
        cout << "True. les caracteres chiffres du telUdM figurent dans telJean." << endl << endl;
    }
    
    // d) afficher les chiffres du num tel Jean qui ni figurent pas dans le num UdeM
    cout << " d) " << endl;
    afficherNumsDansAPasDansB(telJean, telUdM);
    
    // e) afficher les caracteres chiffres impairs du num de Jean
    cout << " e) " << endl;
    string chiffresImpairs = "13579";
    string chiffresPairs = "02468";
    cout << "Afficher les caracteres chiffres impairs du num de Jean" << endl;
    afficherNumsPairsOuImpairs(telJean, chiffresImpairs);
    
    // f) afficher les caracteres chiffres pairs du tel UdeM
    cout << " f) " << endl;
    cout << "Afficher les caracteres chiffres pairs du tel UdeM" << endl;
    afficherNumsPairsOuImpairs(telUdM, chiffresPairs);

    // g) determiner puis afficher :
    // - plus grand carac chiffre du num UdeM
    // - plus petit carac chiffre du num Jean
    cout << " g) " << endl;
    afficherMax(telUdM, "l'UdeM");
    afficherMin(telJean, "Jean");


}
/*
 Execution :
 
 a)
Le telephone de l'Universite de Montreal : (514) 343-6111
Le telephone de Jean : (450) 123-4567

 b)
Il y a 2 fois le caractere chiffre '4' dans le numero de telephone de UdeM
Il y a 4 fois le caractere chiffre '1' dans le numero de telephone de UdeM
Il y a 1 fois le caractere chiffre '7' dans le numero de telephone de Jean

 c)
True. les caracteres chiffres du telUdM figurent dans telJean.

 d)
0 2 7

 e)
Afficher les caracteres chiffres impairs du num de Jean
1 3 5 7

 f)
Afficher les caracteres chiffres pairs du tel UdeM
4 6

 g)
Le plus grand chiffre du numero de telephone de l'UdeM : 6

Le plus petit chiffre du numero de telephone de Jean : 0

Program ended with exit code: 0
 */
