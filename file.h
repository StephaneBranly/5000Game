#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

typedef struct noeud_s{
    struct noeud_s* fg;
    struct noeud_s* fd;
    int score;
    int occ;
} noeud_s;

typedef noeud_s* abr_s;


typedef struct de{
    struct de* de_suivant;
    int valeur;
    int occ;
} de;

typedef de* chain_des;


noeud_s* creer_noeud_s(int);
void ajouter_noeud_s(int, abr_s*);
void afficher_abr_s(abr_s, int);
de* creer_de(int);
void ajouter_de(int, chain_des*);
void supprimer_de(int, chain_des*);
int calcul_points(int, chain_des, int);
void afficher_des(chain_des);
void color(int,int);
int mix_possibilites(chain_des, int, int, abr_s*,int);
int test_possibilites(chain_des, abr_s*);
