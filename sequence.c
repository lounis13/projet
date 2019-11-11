#include "sequence.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char est_nucl(char c) // tester si un char est un nucliotide
{
    return(c == 'A' || c == 'T' || c == 'G' || c == 'C') ; 
}

SEQUENCE Init_Sequence(int taille)
{
    SEQUENCE seq ;

    if((seq.nucleotide =malloc (sizeof(char) * taille) )==NULL ) exit(EXIT_FAILURE);
    return seq ; 
}

void Liberer_Sequence(SEQUENCE seq)
{
    free(seq.nucleotide) ;
}

void Affiche_Sequence(SEQUENCE seq)
{
   for (int i = 0; i < strlen (seq.nucleotide ); i++)
   {
       printf("%2c",seq.nucleotide[i]);
   
   } printf("\n");
   
}

int Taille_Fichier(FILE *fich)
{
    char c ;
    int cpt = 0 ;
    do
    {
        c = fgetc(fich); 
        cpt++;
        if(c != EOF && !est_nucl(c)) { printf("c'est pas une sequence ADN .....") ; exit(0) ;} 
    } while (c != EOF);
    
    rewind (fich);
    return cpt ;
    
}
SEQUENCE Lire_Sequence_DepuisFich(char *nomFichier)
{
    FILE *fichier = fopen(nomFichier , "r"); 
    if(fichier == NULL) exit(EXIT_FAILURE);
    SEQUENCE seq = Init_Sequence (Taille_Fichier(fichier)) ;
    fscanf(fichier , "%s" , seq.nucleotide) ; 
    fclose(fichier);
    return seq ;
}

int indice(char c)
{
    if(c == 'A' ) return 0 ;
    if(c == 'C' ) return 1 ;
    if(c == 'G' ) return 2 ;
    if(c == 'T' ) return 3 ;
    return 4 ;
}

    float matriceDes[5][5] = {
                    {0,2,1,2,1.5} ,
                    {2,0,2,1,1.5} ,
                    {1,2,0,2,1.5} ,
                    {2,1,2,0,1.5} ,
                    {1.5,1.5,1.5,0}
                    } ;

float dis_nucl(char c1 , char c2 )
{
     int i = indice (c1) ; int j = indice (c2) ;
     return matriceDes[i][j];
}


float Calculer_Distance1 (SEQUENCE seq1 , SEQUENCE seq2)
{
    float sum = 0 ;
    int i = 0 ;

    while ( i < strlen(seq1.nucleotide ) && i < strlen( seq2.nucleotide))
    {
        sum = sum + dis_nucl(seq1.nucleotide[i] , seq2.nucleotide[i]) ;
        i++ ;
    }

    while ( i <  strlen(seq1.nucleotide ))
    {
        sum += 1.5 ;
        i++ ;
    }
    while (i < strlen(seq2.nucleotide ))
    {
        sum += 1.5 ;
        i++  ;
    }

    return sum ;
    
}

float Min3 (float f1 , float f2 , float f3)
{
    float min = f1 ;
    if (f2 < min ) min = f2 ;
    if (f3 < min ) min = f3 ;
    return min ;
}

float Alignement (SEQUENCE seq1 , int i , SEQUENCE seq2 , int j)
{
   
      if( i == 0 && j == 0  ) return  dis_nucl (seq1.nucleotide[i] ,seq2.nucleotide[j] );
      else if ( i == -1 && j >= 0 ) return (j+1)*(1.5) ;
      else if ( i>= 0  && j == -1 ) return (i+1)*(1.5) ;  
      else
      {
           float f1=0 , f2 = 0 , f3 =0 ; 
     
           f1 = Alignement (seq1 , i-1 , seq2 , j-1)+ dis_nucl (seq1.nucleotide[i] ,seq2.nucleotide[j] ) ;
           f2 = Alignement (seq1 , i , seq2 , j-1 ) + dis_nucl (seq1.nucleotide[i], ' ') ;
           f3 = Alignement (seq1 , i-1 , seq2 , j ) + dis_nucl (' ' , seq2.nucleotide[j]) ; 
           return Min3 (f1 , f2 ,f3 ) ;
      }

      
}

float Calculer_Distance2(SEQUENCE seq1 , SEQUENCE seq2)
{
    return Alignement ( seq1 , strlen (seq1.nucleotide )-1, seq2 , strlen(seq2.nucleotide)-1) ;

}

/*************************** LES FONCTION POUR MANIPULER LE TABLEAU DE SEQUENCE*********************/

int nbr_lignes(char *nomFich)
{   
    FILE *fichier = fopen(nomFich,"r");
    char c ; int cpt = 0 ;
    do
    {
         c = fgetc(fichier) ;
         if(c == '\n') cpt++ ;
    } while (c!=EOF);
    fclose(fichier);
    return cpt ;
    
}

TAB_SEQUENCE Init_Tab_Sequence (int taille)
{
    TAB_SEQUENCE tab_Seq ;
    tab_Seq.taille = taille ;
    tab_Seq.tab = malloc (sizeof(SEQUENCE) * taille) ;
    return tab_Seq ; 
}
TAB_SEQUENCE Tableau_de_Sequence (char *repertoire)
{
    char cmd [50] ;
    sprintf (cmd,"ls -1 %s >fich_nomFich",repertoire); // le fichier fich_nomFich a les nom des fichier Seq ADN 
    system(cmd);
    int taille = nbr_lignes("fich_nomFich") ;
    FILE *fich = fopen("fich_nomFich","r"); 
    TAB_SEQUENCE tab_seq = Init_Tab_Sequence(taille); 
    for (int i = 0; i < tab_seq.taille; i++)
    {
        char Fich[10];
        char repFich[50] ;
        fscanf(fich,"%s",Fich);
        sprintf(repFich,"%s/%s",repertoire,Fich);
        tab_seq.tab[i] = Lire_Sequence_DepuisFich(repFich);
    }
    
    fclose(fich);
    return tab_seq ;
}


void AfficheTabSeq (TAB_SEQUENCE Tabseq) 
{
    for (int i = 0; i < Tabseq.taille ; i++)
    {
        Affiche_Sequence(Tabseq.tab[i]) ;
    }
    
}


void Liberer_Tab_Sequence(TAB_SEQUENCE tabSeq) 
{
    for (int i = 0; i < tabSeq.taille; i++)
    {
        Liberer_Sequence(tabSeq.tab[i]);
    }
    free(tabSeq.tab);
    
}































