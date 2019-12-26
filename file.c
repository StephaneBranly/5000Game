#include "file.h"

noeud_s* creer_noeud_s(int score){
    noeud_s* nouveau;
    nouveau = malloc(sizeof(noeud_s));
    nouveau->occ=1;
    nouveau->score=score;

    nouveau->fd=NULL;
    nouveau->fg=NULL;

    return nouveau;
}

void ajouter_noeud_s(int score, abr_s* abr){
    noeud_s* actu = *abr;
    noeud_s* pere = *abr;
    if(actu == NULL)
        *abr = creer_noeud_s(score);
    else{
        while(actu != NULL){
            if(actu->score < score){
                pere = actu;
                actu = actu->fd;
            }
            else if(actu->score > score){
                pere = actu;
                actu = actu->fg;
            }
            else{
                actu->occ++;
                pere = NULL;
                actu = NULL;
            }
        }
        if(pere != NULL){
            if(pere->score < score)
                pere->fd = creer_noeud_s(score);
            else
                pere->fg = creer_noeud_s(score);
        }
    }
}

void afficher_abr_s(abr_s abr, int nbr_tests){
    if(abr!=NULL){
        afficher_abr_s(abr->fg,nbr_tests);
        if(abr->score==0)
            color(12,0);
        if(abr->score == 1000000){
            color(10,0);
            printf("\n(%.3f) - REJOUER", ((float)(abr->occ)/nbr_tests));
        }
        else
            printf("\n(%.3f) - %d ",((float)(abr->occ)/nbr_tests),abr->score);
        color(15,0);
        afficher_abr_s(abr->fd,nbr_tests);
    }
}

de* creer_de(int valeur){
    de* nouveau_de;
    nouveau_de = malloc(sizeof(de));
    nouveau_de->occ = 1;
    nouveau_de->valeur = valeur;
    nouveau_de->de_suivant = NULL;

    return nouveau_de;
}

void ajouter_de(int valeur, chain_des* chain){
    de* de_actu = *chain;
    de* de_ancien = *chain;

    if(de_actu==NULL){
        *chain = creer_de(valeur);
    }
    else{
        while(de_actu!=NULL && de_actu->valeur < valeur){
            de_ancien = de_actu;
            de_actu = de_actu->de_suivant;
        }
        if(de_actu==NULL)
            de_ancien->de_suivant = creer_de(valeur);
        else if(de_actu->valeur == valeur)
            de_actu->occ++;
        else{
            de* de_nouv = creer_de(valeur);
            de_nouv->de_suivant = de_actu;
            if(de_actu!=de_ancien)
                de_ancien->de_suivant = de_nouv;
            else
                *chain = de_nouv;
        }
    }
}

void supprimer_de(int valeur, chain_des* chain){
    de* de_actu = *chain;
    de* de_ancien = *chain;

    if(de_actu!=NULL){
        while(de_actu!=NULL && de_actu->valeur < valeur){
            de_ancien = de_actu;
            de_actu = de_actu->de_suivant;
        }
        if(de_actu!=NULL){
            de_actu->occ--;
            if(de_actu->occ==0){
                if(de_actu!=de_ancien)
                    de_ancien->de_suivant = de_actu->de_suivant;
                else
                    *chain = de_actu->de_suivant;;
                free(de_actu);
            }
        }
        else
            printf("Noeud non trouve");
    }
}

int calcul_points(int ancien_s, chain_des chain, int de_triple){
    int score = 0;
    int compteur = 0;
    int marquant = true;
    int suite = true;
    de* de_actu = chain;

    while(de_actu!=NULL){
        if(de_actu->valeur == de_triple)
            score+=de_actu->occ*100;
        else if(de_actu->occ >= 3){
            if(de_actu->valeur == 1)
                score+=1000;
            else
                score+=100*de_actu->valeur;

            if(de_actu->occ-3 >0)
                score+=(de_actu->occ-3)*100;
        }
        else if(de_actu->valeur == 5)
            score+=de_actu->occ*50;
        else if(de_actu->valeur == 1)
            score+=de_actu->occ*100;
        else
            marquant = false;
        if(de_actu->de_suivant!=NULL){
            if(de_actu->valeur!=de_actu->de_suivant->valeur-1 || de_actu->occ>1)
                suite=false;
        }

        compteur+=de_actu->occ;
        de_actu = de_actu->de_suivant;
    }
    if(suite==true && compteur==5)
        return 1000000;
    else
        if((marquant == true && ancien_s != 0) || (marquant == true && compteur==5))
            return 1000000;
        if(score == 0)
            return 0;
        else
            return score+ancien_s;
}

void afficher_des(chain_des chain){
    if(chain!=NULL){
        if(chain->occ > 0){
            int i;
            for(i=0;i<chain->occ;i++){
                switch(chain->valeur){
                    case 1:
                        printf("\n      [     ]");
                        printf("\n      [  o  ]");
                        printf("\n      [     ]\n");
                        break;
                    case 2:
                        printf("\n      [    o]");
                        printf("\n      [     ]");
                        printf("\n      [o    ]\n");
                        break;
                    case 3:
                        printf("\n      [    o]");
                        printf("\n      [  o  ]");
                        printf("\n      [o    ]\n");
                        break;
                    case 4:
                        printf("\n      [o   o]");
                        printf("\n      [     ]");
                        printf("\n      [o   o]\n");
                        break;
                    case 5:
                        printf("\n      [o   o]");
                        printf("\n      [  o  ]");
                        printf("\n      [o   o]\n");
                        break;
                    case 6:
                        printf("\n      [o   o]");
                        printf("\n      [o   o]");
                        printf("\n      [o   o]\n");
                        break;
                }
            }
        }
            //printf("\n[%d]  *%d",chain->valeur,chain->occ);
        afficher_des(chain->de_suivant);
    }
}

void color(int t,int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}

int mix_possibilites(chain_des chain_test, int score_conserve, int de_triple, abr_s* nouveau_abr_s,int nbr_des){
    int nombre_tests=0;
    if(nbr_des >= 1){
        int i;
        for(i=1;i<7;i++){
            ajouter_de(i,&chain_test);
            nombre_tests = mix_possibilites(chain_test, score_conserve, de_triple, nouveau_abr_s, nbr_des-1);
            if(nbr_des == 1)
                ajouter_noeud_s(calcul_points(score_conserve,chain_test,de_triple),nouveau_abr_s);
            supprimer_de(i,&chain_test);
        }
        return 6*nombre_tests;
    }
    return 1;
}

int test_possibilites(chain_des des_conserves, abr_s* nouveau_abr_s){
    de* de_actu = des_conserves;
    chain_des chain_test = NULL;

    int compteur = 0;
    int de_triple = 0;

    int score_conserve = calcul_points(0, des_conserves, 0);

    while(de_actu!=NULL){
        if(de_actu->occ!=0){
            compteur+=de_actu->occ;
            if(de_actu->occ >= 3)
                de_triple = de_actu->valeur;
        }
        de_actu = de_actu->de_suivant;
    }
    printf("\nVotre jeu conserve : ");
    afficher_des(des_conserves);
    printf("\nDe comptant triple : %d",de_triple);
    printf("\nScore jeu conserve (main actuelle) : %d", score_conserve);
    printf("\nNombre des a jouer : %d", 5-compteur);
    printf("\nCalcul de toutes les possibilites...");

    if(5-compteur!=0)
        return mix_possibilites(chain_test,score_conserve,de_triple,nouveau_abr_s,5-compteur);
    return 0;
}

