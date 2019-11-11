#include "sequence.h"

typedef struct DISTANCE
{
    float **Les_Des ;         //
    TAB_SEQUENCE Tab_Seq ;  //    
        
}DISTANCE;

/*
 complexité : linéaire O(n)*/
DISTANCE Gerrer_Distance (char *repertoire) ;
void Liberer_Distance(DISTANCE dist) ;
DISTANCE Remplire_Distance(char *repertoire) ;

void Remplire_LesFichiers_Distance(char *repertoire) ;

