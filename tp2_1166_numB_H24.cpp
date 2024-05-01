//
//  IFT 1166, H24
//  TP2. Numero B
//
//  Auteur: Deanna Wung
//

#include <iostream>
#include <iomanip> // permet de faire setprecision()
using namespace std;

class Employe{
    private :
        string NAS; // format "123 456 678"
        float salHebdo; // exemple 1075.25
    
    public :
        // constructeur de base
        Employe(string NAS, float salHebdo){
            this->NAS = NAS;
            this->salHebdo = salHebdo;
        }
    
        /* constructeur qui prend 3 paramètres pour calculer le sal Hebdo*/
        Employe(string NAS, float nbHresTravailles, float salHoraire){
            this-> NAS = NAS;
            salHebdo = nbHresTravailles * salHoraire;
            /* on assume que ici, "nb d'heures travaillés" représente
            le nb d'hres travaillés par semaine */
        }
    
        void afficher(string intitule){
            cout << setprecision(2);
            cout << intitule << " :\n\tNAS : " << NAS << "\n\tSalaire hebdomadaire : " <<  salHebdo << "$ par semaine" << endl;
        }
    
        string getNAS(){
            return NAS;
        }
        
        float getSalHebdo(){
            return salHebdo;
        }
        
        void setNAS(string NAS){
            this->NAS = NAS;
        }
        
        void setSalHebdo(float salHebdo){
            this->salHebdo = salHebdo;
        }
    
} ;

int main(int argc, const char * argv[]) {
    // format affichage
    cout.setf(ios::fixed); cout.setf(ios::showpoint);
    
    Employe emp1("321 498 726", 987.50),
            emp2("135 444 321", 45.00, 20.00);
    
    emp2.afficher("Informations du deuxieme employe");
    
    return 0;
}

/*
 Execution:
 
 Informations du deuxieme employe :
     NAS : 135 444 321
     Salaire hebdomadaire : 900.00$ par semaine
 Program ended with exit code: 0
 */
