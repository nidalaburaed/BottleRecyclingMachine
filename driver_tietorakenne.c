#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tietorakenne.h"
/* 
gcc komento: "gcc -o d_tieto driver_tietorakenne.c tietorakenne.h"
josta ajettava tiedosto: "./d_tieto"
*/

/*********************************LISÄYS*********************************************************/
Pullo *Lisays(Pullo *pEka, char rivi[255]) {
	Pullo *pLiukuri, *pUusin;
	char *token = NULL;

    /* Muistin varaus */
	if ((pUusin = (Pullo*)malloc(sizeof(Pullo))) == NULL) {
		perror("Muistin varaaminen epäonnistui.");
		exit(1);
	}
	
	/* Tuotetiedoston rivin parsiminen */
	token = strtok(rivi, " ");
	if((pUusin->sTyyppi = malloc(strlen(token)+1)) == NULL) {
		perror("Muistin varaaminen epäonnistui.");
		exit(1);
	}

	strcpy(pUusin->sTyyppi, token);
    pUusin->fTilavuus = atof(strtok(NULL, " "));
    pUusin->fPantti = atof(strtok(NULL, " "));

	pUusin->pSeuraava = NULL;
    
	if (pEka == NULL) {
		pEka = pUusin;
        
	} else {

		pLiukuri = pEka;
		while (pLiukuri->pSeuraava != NULL) {

			pLiukuri = pLiukuri->pSeuraava;
		}
 		pLiukuri->pSeuraava = pUusin;

	}
    
	return pEka;
}

Pullo *MuistinvapautusLisays(Pullo *pEka) {
	Pullo *del = pEka;
	Pullo *seuraava;
	while (del != NULL) {
		printf("%s  %0.3f %0.2f\n", del->sTyyppi, del->fTilavuus, del->fPantti);
		seuraava = del->pSeuraava;
		free(del);
		del = seuraava;
	}
	pEka = NULL;
	return pEka;
}

/*********************************PALAUTUS********************************************************/

Solmu *Palautus(Solmu *pAlku, int nro) {
	Solmu *pLiukuri, *pUusin;

	/* Muistin varaus */
	if ((pUusin = (Solmu*)malloc(sizeof(Solmu))) == NULL) {
		perror("Muistin varaaminen epäonnistui.");
		exit(1);
	}
		
	pUusin->iNro = nro;
	pUusin->pSeuraava = NULL;
 
	if (pAlku == NULL) {
		pAlku = pUusin;
        
	} else {

		pLiukuri = pAlku;
		while (pLiukuri->pSeuraava != NULL) {
			pLiukuri = pLiukuri->pSeuraava;
		}
 		pLiukuri->pSeuraava = pUusin;
	}
    
	return pAlku;
}

Solmu *MuistinvapautusPalautus(Solmu *pAlku) {
	Solmu *del = pAlku;
	Solmu *seuraava;
	while (del != NULL) {
		printf("%d\n", del->iNro);
		seuraava = del->pSeuraava;
		free(del);
		del = seuraava;
	}
	pAlku = NULL;
	return pAlku;
}


/****************************KAPPALEMÄÄRÄ***********************************************************/

int KPL(Solmu *pAlku, int nro) {
	int kpl = 0;

	while (pAlku != NULL) {
		if(pAlku->iNro == nro) {
			kpl++;
		}		
		pAlku = pAlku->pSeuraava;
	}

	return kpl;
}

/****************************TIETYN*ALKION*PALAUTUS***********************************************/

Pullo *Tiettyalkio(Pullo *pLiukuri, int nro) {
	int i = 1;

	while (pLiukuri != NULL) {
		if(i == nro) {
			return pLiukuri;
		}		
		pLiukuri = pLiukuri->pSeuraava;
		i++;
	}

	/* Mikäli alkion nro jota ei jostain syystä ole listalla. */
	return pLiukuri;
}
/*********************************PÄÄOHJELMAN*TESTIT*********************************************/
int main(void) {
/*********************************LISÄYS*MUUTTUJAT***********************************************/
	Pullo *pEka = NULL;
	char rivi1[255] = "pullo 1.5 0.40";
	char rivi2[255] = "tölkki 0.33 0.15";
	char rivi3[255] = "tyhjä 0.313 0.25";

/*********************************PALAUTUS*MUUTTUJAT**********************************************/
	Solmu *pAlku = NULL;
	int nro1 = 1, nro2 = 2, nro3 = 3, nro4 = 3;

/****************************TIETYN*ALKION*PALAUTUS*MUUTTUJAT*************************************/
	Pullo *pTietty = NULL;

/******************************************TESTIT*************************************************/
	
	printf("KAPPALEMÄÄRÄ TYHJÄ: \n%d = 0\n", KPL(pAlku, nro1));	

	pEka = Lisays(pEka, rivi1); /*Lisätään alkiot linkitettyyn listaan yksi kerrallaan*/
	pEka = Lisays(pEka, rivi2);
	pEka = Lisays(pEka, rivi3);

	pTietty = Tiettyalkio(pEka, 3); /*Haetaan tietyn alkion tiedot*/
	printf("3. solmu: %s %.2fl\n", pTietty->sTyyppi, pTietty->fTilavuus);
	pTietty = Tiettyalkio(pEka, 1);
	printf("1. solmu: %s %.2fl\n", pTietty->sTyyppi, pTietty->fTilavuus);
	pTietty = Tiettyalkio(pEka, 5);
	printf("%p\n", pTietty); /* Tulostaa osoittimen muistipaikan */

	
	printf("LISÄYS OBJEKTIT:\n");
	pEka = MuistinvapautusLisays(pEka); /*Vapautetaan muisti ja tarkastetaan listan tiedot tulosteella*/

	pAlku = Palautus (pAlku, nro1); /*Lisätään alkiot linkitettyyn listaan yksi kerrallaan*/
	pAlku = Palautus (pAlku, nro2);
	pAlku = Palautus (pAlku, nro3);
	pAlku = Palautus (pAlku, nro4);

	printf("KAPPALEMÄÄRÄ OBJEKTIT:\n"); /*Tarkistetaan kappalemäätän return arvo*/
	printf("%d = 1\n", KPL(pAlku, 1));
	printf("%d = 2\n", KPL(pAlku, 3));
	printf("%d = 0\n", KPL(pAlku, 5));
	
	printf("PALAUTUS OBJEKTIT:\n");
	pAlku = MuistinvapautusPalautus(pAlku); /*Vapautetaan muisti ja tarkastetaan listan tiedot tulosteella*/

	return 0;
}