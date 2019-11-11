#include "distance.h"
#include <stdlib.h>
#include <stdio.h>

int Tdist(DISTANCE dist)
{
    return dist.Tab_Seq.taille ;
}

void Liberer_Distance(DISTANCE dist)
{
    for (int i = 0; i < Tdist(dist); i++)
    {
        free(dist.Les_Des[i]) ;
    }
    free(dist.Les_Des) ;
    Liberer_Tab_Sequence(dist.Tab_Seq);
}

DISTANCE Gerrer_Distance (char *repertoire) 
{
    DISTANCE dist ;
    dist.Tab_Seq = Tableau_de_Sequence(repertoire) ;
    dist.Les_Des = malloc (sizeof(int*)* Tdist(dist));
    for (int i = 0; i < Tdist(dist); i++)
    {
        dist.Les_Des[i] = malloc (sizeof(int)*(i+1)) ;
    }
    return dist ;
}

DISTANCE Dis_Entre_Seq(DISTANCE dis)
{
    SEQUENCE seq1 ;
    SEQUENCE seq2 ;
    for ( int i = 0; i < dis.Tab_Seq.taille ; i++)
    {
        for (int j = 0; j <= i; j++)
        {
        seq1 = dis.Tab_Seq.tab[i] ; 
        seq2 = dis.Tab_Seq.tab[j] ;
        dis.Les_Des[i][j] = Calculer_Distance1(seq1,seq2) ;

    }

    }
    return dis ;
}

DISTANCE Remplire_Distance(char *repertoire) 

{   
    DISTANCE dist = Gerrer_Distance (repertoire) ;
    return  Dis_Entre_Seq(dist) ;
    
}

void Distance_dans_Fichier(DISTANCE dist ,int ligne , char *nomFichier)
{
     FILE *fichier ;
     
     if ((fichier =fopen (nomFichier,"w"))== NULL) exit(0) ;
     int i = ligne , j = 0 ;
     while (i < Tdist (dist) && j < Tdist (dist) )
     {
         if(j < i) 
         {
             fprintf(fichier,"%f %s\n",dist.Les_Des[i][j],dist.Tab_Seq.tab[j].nucleotide);
             j++ ;
         }
         else
         {
              fprintf(fichier,"%f %s\n",dist.Les_Des[i][j],dist.Tab_Seq.tab[i].nucleotide);
              i++ ;
         }
         
     }
     fclose(fichier);
     
}



void Remplire_LesFichiers_Distance(char *repertoire)
{
    DISTANCE dist = Remplire_Distance (repertoire) ;
    for (int i = 0; i < Tdist(dist); i++)
    {
        char nomFichier[30] ;
        if(i<10)sprintf(nomFichier,"Distances/dist0%d.txt",i+1);
        else sprintf(nomFichier,"Distances/dist%d.txt",i+1)   ;
        Distance_dans_Fichier(dist,i,nomFichier) ;
    }
    Liberer_Distance(dist);
    
}

