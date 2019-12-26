#include "file.h"

int main(){
    color(15,0);
    abr_s nouveau_abr_s = NULL;
    int valeur_de=1;
    chain_des chain = NULL;
    color(10,0);
    printf("Le jeu des 5000\n\n");
    printf("Rentrez vos des conserves :\n (0 pour arreter)\n");
    color(15,0);
    while(valeur_de!=0){
        scanf("%d",&valeur_de);
        if(valeur_de!=0)
            ajouter_de(valeur_de,&chain);
    }

    int nbr_tests=test_possibilites(chain,&nouveau_abr_s);

    color(10,0);
    printf("\nNbr de tests effectues : %d",nbr_tests);
    printf("\nVos probabilites de gagner :");
    color(15,0);
    afficher_abr_s(nouveau_abr_s,nbr_tests);
}
