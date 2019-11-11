
typedef struct sequence
{
    char *nucleotide ;

}SEQUENCE;

typedef struct TAB_SEQUENCE
{
    SEQUENCE *tab ;
    int taille ;
}TAB_SEQUENCE;

/*initialiser la sequence ADN avec malloc la taille des fichier 
 complexité : constante O(1)*/
SEQUENCE Init_Sequence(int taille) ;
/*
complexité : constante O(1)*/
void Liberer_Sequence(SEQUENCE seq);

/*Afiche la sequence ADN 
 complexité : linéaire O(n) */
void Affiche_Sequence (SEQUENCE seq) ;

/*
 complexité : linéaire O(n) depand de la taille de fichier*/
SEQUENCE Lire_Sequence_DepuisFich(char *nomFichier) ;


/*
 complexité : linéaire O(n)*/
float Calculer_Distance1(SEQUENCE seq1 , SEQUENCE seq2);


/*
complexité :  O(n*m)*/
float Calculer_Distance2(SEQUENCE seq1 , SEQUENCE seq2);

TAB_SEQUENCE Tableau_de_Sequence (char *repertoire) ;

void AfficheTabSeq (TAB_SEQUENCE Tabseq) ;


void Liberer_Tab_Sequence(TAB_SEQUENCE tabSeq) ;