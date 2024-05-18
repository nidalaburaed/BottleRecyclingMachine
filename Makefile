program: program.o tiedostonkasittely.o tietorakenne.o apufunktiot.o
	gcc program.o tiedostonkasittely.o tietorakenne.o apufunktiot.o -o program -Wall
program.o: program.c tiedostonkasittely.h tietorakenne.h apufunktiot.h
	gcc program.c -c -Wall -std=c99 -pedantic -W
tiedostonkasittely.o: tiedostonkasittely.c tiedostonkasittely.h tietorakenne.h apufunktiot.h
	gcc tiedostonkasittely.c -c -Wall -std=c99 -pedantic -W
tietorakenne.o: tietorakenne.c tietorakenne.h apufunktiot.h
	gcc tietorakenne.c -c -Wall -std=c99 -pedantic -W
apufunktiot.o: apufunktiot.c apufunktiot.h
	gcc apufunktiot.c -c -Wall -std=c99 -pedantic -W