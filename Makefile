valgrind : main1
	valgrind ./main1 sequences_ADN/

partie1 : main1
	./main1 sequences_ADN/

main1 : main1.o distance.o sequence.o
	gcc main1.o distance.o sequence.o -g -o main1

main1.o : main1.c
	gcc -Wall -c -g main1.c

sequence.o : sequence.c sequence.h
	gcc -Wall -c -g sequence.c

distance.o : distance.c distance.h Distances
	
	gcc -Wall -c -g distance.c 

Distances : 
	mkdir Distances
clean :
	rm -f main1
	rm -f sequence.o
	rm -f distance.o 
	rm -f main1.o
	rm -f fich_nomFich
	rm -rf Distances
	