#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apufunktiot.h"
#include "tietorakenne.h"

/* gcc komento: "gcc -o d_program driver_program.c"

/**************ALKUVALIKKO***************/

int lueSyoteInt(char *buffer, int *virhe_lippu){
	*virhe_lippu = 0;
	long luku = 1;

	return (int)luku;
}


int Alkuvalikko(void) {
	int valinta, virhe_lippu;
	char buffer[MAX];

	do {
		do{
			printf("PULLONPALAUTUSAUTOMAATTI\n\n"
			"Automaatti on valmis ottamaan vastaan pullot ja tölkit.\n\n"
			"1) Aloita palautus\n"
			"0) Lopeta\n\n"
			"Valitse: ");

			virhe_lippu = 0;
		
			valinta = lueSyoteInt(buffer, &virhe_lippu);
			printf("%d", valinta);
		}while(virhe_lippu != 0);

		if ((valinta > 1) || (valinta < 0)) {
			printf("\nVäärä valinta!\n\n");
		}

	} while ((valinta != 0) && (valinta != 1));

    
	return valinta;
}

/********************************PALAUTUSVALIKKO*********************************/

/****PALAUTUS***/
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



/******LINKITETYN*LISTaAN*LISÄÄMINEN****/
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


/******TILAPISLOKIN*PÄÄLLEKIRJOITUS**/
int Loki() {
	return 0;
}

/****TIETNY*ALKION*PALAUTUS****/

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

Solmu *Palautusvalikko(Pullo *pEka) {
	Solmu *pAlku = NULL;
	Pullo *pLiukuri = NULL, *pTietty = NULL;
	int valinta = 0, lopetus, i = 1;

	/* Lokitiedoston päällekirjoitus*/
	Loki();
	printf("LOKI PÄÄLLEKIRJOITETTU\n");

	do {
		pLiukuri = pEka;
		printf("Syötä uusi pullo tai tölkki.\n\n");
		
		while (pLiukuri != NULL) {
			printf("%d) %s %.2fl\n",i++ , pLiukuri->sTyyppi, pLiukuri->fTilavuus);
			pLiukuri = pLiukuri->pSeuraava;		
		}

		printf("%d) Lopeta syöttö ja tulosta kuitti.\n"
			"--> ", i);
		lopetus = i;
		i = 1;
		
		/* Kokonaisluku tarkistus */
		if (scanf("%d", &valinta) != 1) {
			printf("\nVäärä valinta!\n\n");

		/* Oikean välin tarkistus */
		} else if ((valinta < 1) || (valinta > lopetus)) {
			printf("\nVäärä valinta!\n\n");

		} else if (valinta < lopetus) {
			pTietty = Tiettyalkio(pEka, valinta);
			printf("Syötetty: %s %.2fl\n", pTietty->sTyyppi, pTietty->fTilavuus);

			pAlku = Palautus(pAlku, valinta);			
			//Temploki(pTietty);
		}
		//clearstream();
	} while (valinta != lopetus);

	return pAlku;
}



/*********************************TULOSTUS**************/






/*********************************PÄÄOHJELMA******************************************************/

int main(void) {
	Solmu *pAlku = NULL;
	Pullo *pEka = NULL;
    int valinta;
    
    int nro1 = 1;

	char rivi1[255] = "pullo 1.5 0.40";
	char rivi2[255] = "tölkki 0.33 0.15";
	char rivi3[255] = "tyhjä 0.313 0.25";
/**************************TESTATAAN ALKUVALIKON VALINTA**********************/
valinta = Alkuvalikko();
printf("\nALKUVALIKKO PALAUTTAA valinnan: %d", valinta);
/**************************TESTATAAN PALAUTUSVALIKKOON SYÖTETTY ALKIO*****/
pEka = Lisays(pEka, rivi1);
pEka = Lisays(pEka, rivi2);

pAlku = Palautusvalikko(pEka);
printf("Palautusvalikon paluuarvo: %d", pAlku->iNro);
	return 0;
}