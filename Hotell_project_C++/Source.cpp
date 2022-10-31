#include<iostream>
#include<string>								// stringit k�ytt��n
#include<cmath>									// Otetaan matikka kirjasto k�ytt��n varmuuden varalta, jos on tarvetta
#include<ctime>									// Otetaan tietokoneen kello k�ytt��n
#include<iomanip>								// otetaan k�ytt��n kirjasto sy�tteen tarkastuksen tarkkuuteen.
#include<windows.h>

using namespace std;



// Creating a structure class for names and reservation numbers
struct hotelli {

	string nimi = " ";
	int varausNro = 0;

};

int syoteValikko();															// Luodaan aliohjelma, jossa voidaan valikolle tehd� oma tarkastus
int syoteTarkastus();														// Luodaan aliohjelma, jossa tarkistetaan sy�tteet
void hinnasto(int huoneet);													// Luodaan aliohjelma, jossa voidaa esitt�� hinnasto
void tarkastaVapaat(struct hotelli varaaja[], int& vapaatHuoneet);						// Luodaan aliohjelma, jossa voidaan tarkastaa varatut huoneet
void taulukot2(struct hotelli varaaja[], int& vapaatHuoneet);				// Luodaan alihjelma, jossa voidaan varata huoneita
void taulukot3(struct hotelli varaaja[], int& vapaatHuoneet);				// Luodaan aliohjelma jossa voidaan k�sitell� jatkovarauksia
void varausTarkastus(struct hotelli varaaja[], int& vapaatHuoneet);			// Luodaan aliohjelma, jossa voidaan tarkastaa varatut huoneet
void varauksenPeruutus(struct hotelli varaaja[], int& vapaatHuoneet);		// Luodaan aliohjelma, jossa voidaan peruuttaa varauksia
void varausTarkastus_nimi(struct hotelli varaaja[], int& vapaatHuoneet);
void varausPeruutus_nimi(struct hotelli varaaja[], int& vapaatHuoneet);


const int huoneMaara = 300;							// Luodaan muutama globaali vakio huoneille ja hinnoille
const int hinta1 = 100;
const int hinta2 = 80;



int main() {
	SetConsoleCP(1252);							// T�ll� komennolla saadaan my�s k�ytt�j�n sy�tt�m�t ��kk�set n�kyviin
												// Vaatii <windwos.h> kirjaston toimiakseen

	srand(time(0));								//T�ll� komennolla saadaan varausnumero generoimaan aina uudet numerot
	setlocale(LC_ALL, "Finnish");

	hotelli varaaja[huoneMaara];
	int valinta;
	int vapaatHuoneet = 300;


	for (int i = 0; i < 300; i++) {
		varaaja[i].nimi = "---";
		varaaja[i].varausNro = 0;
	}

	do {
		system("cls");							// T�t� komentoa on ripoteltu v�lill� pyyhkim��n konsolin, jotta se pysyy puhtaamman n�k�isen�

	p1:											// komento siis pyyhkii konsolin puhtaaksi
												// p1 palautuspiste.... Palautuspisteit� l�ytyy v�lill� vaihtamaan ohjelman suuntaa riippuen k�ytt�j�n valinnoista
		cout << endl << endl;
		cout << "----------------------------------------------------------------" << endl << endl;
		cout << "\t" << "TERVETULOA KARAMIN HOTELLIIN " << endl << endl;
		cout << "----------------------------------------------------------------" << endl << endl;
		cout << " Mit� haluaisit tehd�?" << endl << endl;

		cout << " 1: Varaa huone" << endl;
		cout << " 2: tarkista hinnasto" << endl;
		cout << " 3: Tarkasta varaus varausnumerolla" << endl;
		cout << " 4: Tarkasta varaus nimell�" << endl;
		cout << " 5: Peruuta varaus varausnumerolla" << endl;
		cout << " 6: Peruuta varaus nimell�" << endl;
		cout << " 7: Tarkasta vapaana olevat huoneet" << endl;
		cout << " 8: poistu" << endl << endl;

		// K�ytt�j�n sy�tt� l�htee erilliseen aliohjelmaan tarkastamaan sy�tt�� ja palauttaa takaisin, jos sy�te on hyv�ksytty
		valinta = syoteValikko();

		// toinen sy�tteen tarkastus, jos sy�tteeseen tulee v��r� numeroarvo ohjelma palauttaa pisteeseen p1 ja l�htee suorittamaan uudestaan

		if (valinta < 1 || valinta > 8) {
			cout << endl;
			system("cls");
			cout << endl << endl;
			cout << "Virheellinen valinta! Yrit� uudestaan...";
			goto p1;
		}


		else if (valinta == 1) {
			taulukot2(varaaja, vapaatHuoneet);					// l�hdet��n varamaan huoneita aliohjelmaan
		}

		else  if (valinta == 2) {
			hinnasto(valinta);												// kutsutaan hinnasto aliohjelmaa
		}

		else if (valinta == 3) {

			varausTarkastus(varaaja, vapaatHuoneet);				// L�hdet��n tarkastamaan varauksia
		}

		else if (valinta == 4) {

			varausTarkastus_nimi(varaaja, vapaatHuoneet);						// L�hdet��n peruuttamaan varauksia

		}


		else if (valinta == 5) {

			varauksenPeruutus(varaaja, vapaatHuoneet);						// L�hdet��n peruuttamaan varauksia

		}

		else if (valinta == 6) {

			varausPeruutus_nimi(varaaja, vapaatHuoneet);						// L�hdet��n peruuttamaan varauksia

		}

		else if (valinta == 7) {

			tarkastaVapaat(varaaja, vapaatHuoneet);


		}

	} while (valinta != 8); {												// Jos k�ytt�j� sy�tt�� numeron 6, niin ohjelma lopettaa
		cout << endl;
		system("cls");
		cout << endl;
		cout << "************************************************" << endl << endl;
		cout << "Kiitos k�ynnist� ja Tervetuloa uudestaan!" << endl << endl;
		cout << "************************************************" << endl;
	}


}


// Alihojelma, jossa voidaan tehd� huonevarauksia
// Aliohjelmaan l�hetet��n taulukko ja vapaiden huoneiden m��r�
void taulukot2(struct hotelli varaaja[], int& vapaatHuoneet) {
	setlocale(LC_ALL, "Finnish");
	string nimi;
	int huoneVaraus;
	int paivat;
	srand(time(0));
	system("cls");
p2:
	cout << "Huoneita vapaana: " << vapaatHuoneet << endl;
	cout << "Valitse huoneen numero, jonka haluaisit varata? (1-300) ";

	huoneVaraus = syoteTarkastus();												// Valinta l�htee sy�tteen tarkastukseen

	if (huoneVaraus < 1 || huoneVaraus > 300) {
		cout << "Virheellinen valinta! Yrit� uudestaan..." << endl << endl;
		goto p2;

	}
	// Tarkastetaan onko huone vapaa. Jos valitun huoneen alkion arvo on suurempi kuin 0, ohjelma ilmoittaa huoneen olevan varattu
	// Mukana on my�s palautus piste p2 joka l�hett�� ohjelman suorittamaan uudestaan, jos huone on varattu
	else if (varaaja[huoneVaraus - 1].varausNro > 0) {

		cout << endl << endl;
		cout << "T�m� huone on valitettavasti jo varattu" << endl << endl;
		goto p2;
	}
	// Jos huone on vapaa, niin silloin m��ritet��n sen arvo generoidulla varausnumerolla, jotta se muuttuu varatuksi
	// Jos huone voidaan varata, pudotetaan vapaiden huoneiden m��r�� yhdell�
	else if (varaaja[huoneVaraus - 1].varausNro < 1) {

		vapaatHuoneet--;

		varaaja[huoneVaraus - 1].varausNro = (rand() % 90000) + 9999;

	}

	// pyydet��n k�ytt�j�lt� vietetyt y�t, jotta voidaan laskea summa laskulle

	cout << "Montako y�t� haluaisit viett��? ";
	paivat = syoteTarkastus();


	cout << endl;


	cout << "Sy�t� viel� koko nimesi: ";
	getline(cin, varaaja[huoneVaraus - 1].nimi);
	cout << endl;

	cout << "Kiitos! " << varaaja[huoneVaraus - 1].nimi << " Huoneesi on nyt varattu!" << endl << endl;
	cout << "Laskusi summa on: " << (paivat - 1) * hinta2 + hinta1 << " euroa, joka maksetaan kirjautumisen yhteydess�" << endl;		// lasketaan summa varaukselle
	cout << endl;
	cout << "T�m�n huoneen varausnumero on: " << varaaja[huoneVaraus - 1].varausNro << endl << "(Varausnumerolla voit tarkastaa ja peruuttaa varauksia, pid� se siis tallessa)" << endl << endl;
p3:
	cout << "Huoneita vapaana: " << vapaatHuoneet << endl;

	cout << "Haluaisitko jatkaa varaamista? (1 = Kyll� 2 = Ei) ";
	int valinta2;
	valinta2 = syoteTarkastus();


	if (valinta2 < 1 || valinta2 > 2) {
		cout << endl;
		cout << "Virheellinen valinta! Yrit� uudestaan" << endl << endl;
		goto p3;
	}



	// T�SS� MENOSSA-------------------------------- 1.2.2022



	else if (valinta2 == 1) {						// Jos halutaan jatkaa varaamista, kutsutaan toista aliohjelmaa, jossa voidaan antaa uusia varausnumeroita
		taulukot3(varaaja, vapaatHuoneet);
	}

	else if (valinta2 == 2) {
		cout << "Selv� palataan p��valikkoon" << endl << endl;
		cout << "----------------------------------" << endl << endl;

	}

}

// Toinen aliohjelma, jossa voidaan tehd� jatkovarauksia huoneille
// Alihojelmaan l�hetet��n taulukko, vanha varausnumero ja vapaiden huoneiden m��r�

void taulukot3(struct hotelli varaaja[], int& vapaatHuoneet) {
	setlocale(LC_ALL, "Finnish");
	int huoneVaraus;
	string nimi;

	cout << endl << endl;
	system("cls");
p2:
	cout << "Huoneita vapaana: " << vapaatHuoneet << endl;
	cout << "Mink� huoneen haluaisit varata? (1-300) ";

	huoneVaraus = syoteTarkastus();


	if (huoneVaraus < 1 || huoneVaraus > 300) {
		cout << "Virheellinen valinta! Yrit� uudestaan..." << endl << endl;
		goto p2;

	}
	// Tarkastetaan onko huone vapaa. Jos valitun huoneen alkion arvo on suurempi kuin 0, ohjelma ilmoittaa huoneen olevan varattu
	// Mukana on my�s palautus piste p2 joka l�hett�� ohjelman suorittamaan uudestaan, jos huone on varattu
	else if (varaaja[huoneVaraus - 1].varausNro > 0) {

		cout << endl << endl;
		cout << "T�m� huone on valitettavasti jo varattu" << endl << endl;
		goto p2;
	}
	// Jos huone on vapaa, niin silloin m��ritet��n sen arvo 1, jotta se muuttuu varatuksi
	// Pudotetaan my�s vapaiden huoneiden m��r��
	else if (varaaja[huoneVaraus - 1].varausNro == 0) {
		vapaatHuoneet--;
		varaaja[huoneVaraus - 1].varausNro = (rand() % 90000) + 9999;
	}

	// pyydet��n k�ytt�j�lt� vietetyt y�t, jotta voidaan laskea summa laskulle

	cout << "Montako y�t� haluaisit viett��? ";
	int paivat;
	paivat = syoteTarkastus();

	cout << endl;

	cout << "Sy�t� viel� koko nimesi: ";
	getline(cin, varaaja[huoneVaraus - 1].nimi);
	cout << endl;


	//M��ritet��n varatun huoneen alkio varausnumeroksi, jotta voidaan my�hemmin hakea varauksia numeroilla	


	cout << "Kiitos! " << varaaja[huoneVaraus - 1].nimi << " Huoneesi on nyt varattu!" << endl << endl;
	cout << "Laskusi summa on: " << (paivat - 1) * hinta2 + hinta1 << " euroa, joka maksetaan kirjautumisen yhteydess�" << endl;		// lasketaan summa varaukselle

	cout << "T�m�n huoneen varausnumero on: " << varaaja[huoneVaraus - 1].varausNro << endl << "(Varausnumerolla voit tarkastaa ja peruuttaa varauksia, pid� se siis tallessa)" << endl << endl;

p3:
	cout << "Huoneita vapaana: " << vapaatHuoneet << endl;
	cout << "Haluaisitko jatkaa varaamista? (1 = Kyll� 2 = Ei) ";
	int valinta2;
	valinta2 = syoteTarkastus();


	if (valinta2 < 1 || valinta2 > 2) {					// Jos tulee virheellinen sy�tt�, palautetaan pisteeseen p3
		cout << endl;
		cout << "Virheellinen valinta! Yrit� uudestaan.";
		cout << endl << endl;
		goto p3;
	}

	else if (valinta2 == 1) {							// Jos k�ytt�j� haluaa jatkaa varaamista, l�hdet��n suorittamaan t�t� aliohjelmaa uudestaan
		goto p2;										// Eli palautetaan pisteeseen p2, joka on alihojelman alussa
	}

	else if (valinta2 == 2) {								// Jos ei haluta jatkaa varaamista, annetaan aliohjelman palata takaisin p��ohjelmaan

		cout << endl;
		cout << "Selv�! Palataan takaisin valikkoon!" << endl << endl;
		cout << "---------------------------------------------------------" << endl << endl;
	}

}

// Alihojelma, jossa voidaan tarkastaa varauksia
// Alihojelmaan l�hetet��n taulukko, varausnumero ja vapaat huoneet
void varausTarkastus(struct hotelli varaaja[], int& vapaatHuoneet) {
	setlocale(LC_ALL, "Finnish");
	int varausNroTarkistus;

	cout << endl << endl;
	system("cls");
p1:
	cout << endl;

	cout << "Sy�t� varausnumerosi: " << endl;

	varausNroTarkistus = syoteTarkastus();



	cout << endl << endl;

	if (varausNroTarkistus == 0) {
		cout << "Virheellinen valinta. Yrit� uudestaan.";
		goto p1;
	}


	// Kun k�ytt�j� on sy�tt�nyt varausnumeron, ohjelma l�htee suorittamaan loopin ja vertaamaan alkioiden arvoja
	// Jos looppi l�yt�� alkion, jonka arvo vastaa varausnumeroa looppi breakkaa ja hypp�� seuraavaan ilmoitettuun pisteeseen
	// Jos ei l�yd�, niin ohjelma ilmoittaa asiasta ja kysyy haluaako k�ytt�j� sy�tt�� uuden numeron
	for (int i = 0; i < 300; i++) {
		if (varaaja[i].varausNro == varausNroTarkistus) {

			cout << "T�ll� numerolla l�ytyy varaus j�rjestelm�st�." << endl << "Varatun huoneen numero: " << i + 1;
			cout << endl << endl;
			goto x1;
			break;

		}


	}

	cout << "Numerolla ei l�ytynyt varausta j�rjestelm�st�." << endl << endl;
x1:
	// Ohjelma kysyy, haluaako k�ytt�j� antaa uuden numeron
	// Jos k�ytt�j� haluaa, niin ohjelma palaa t�m�n alihojelman alkuun
	// Jos ei, niin aliohjelma palautuu p��ohjelmaan
	cout << "Haluaisitko sy�tt�� uuden varausnumeron vai palata p��valikkoon? " << endl;
	cout << "1 = Sy�t� uusi varausnumero" << endl << "2 = Palaa p��valikkoon ";
x2:
	int paatos;
	paatos = syoteTarkastus();


	if (paatos > 2 || paatos < 1) {
		cout << endl;

		cout << "Virheellinen valinta! Yrit� uudestaan." << endl;
		goto x2;

	}

	if (paatos == 1) {

		goto p1;

	}

	else if (paatos == 2) {

		cout << endl;

	}

	cout << "Palataan p��valikkoon" << endl << endl;
	cout << "-------------------------------------------------------------------------------------" << endl << endl;
}
/*Aliohelma, jossa voidaan tarkastaa varaukset k�ytt�m�ll� nime�*/

void varausTarkastus_nimi(struct hotelli varaaja[], int& vapaatHuoneet) {
	setlocale(LC_ALL, "Finnish");
	string varaus_tarkastus;

	cout << endl << endl;
	system("cls");
beginning:

	cout << endl;

	cout << "Sy�t� nimesi: ";

	getline(cin, varaus_tarkastus);

	cout << endl << endl;

	// Kun k�ytt�j� on sy�tt�nyt varausnumeron, ohjelma l�htee suorittamaan loopin ja vertaamaan alkioiden arvoja
	// Jos looppi l�yt�� alkion, jonka arvo vastaa varausnumeroa looppi breakkaa ja hypp�� seuraavaan ilmoitettuun pisteeseen
	// Jos ei l�yd�, niin ohjelma ilmoittaa asiasta ja kysyy haluaako k�ytt�j� sy�tt�� uuden numeron
	bool testi = false;
	for (int i = 0; i < 300; i++) {
		if (varaaja[i].nimi == varaus_tarkastus) {

			cout << "T�ll� nimell� l�ytyy varaus j�rjestelm�st�." << endl << "Varatun huoneen numero: " << i + 1;
			cout << endl << endl;
			testi = true;

		}

	}
	if (testi == false) {
		cout << "T�ll� nimell� ei l�ytynyt varausta j�rjestelm�st�. " << endl << endl;
	}


x1:
	// Ohjelma kysyy, haluaako k�ytt�j� antaa uuden numeron
	// Jos k�ytt�j� haluaa, niin ohjelma palaa t�m�n alihojelman alkuun
	// Jos ei, niin aliohjelma palautuu p��ohjelmaan
	cout << "Haluaisitko sy�tt�� uuden nimen vai palata p��valikkoon? " << endl;
	cout << "1 = Sy�t� uusi nimi" << endl << "2 = Palaa p��valikkoon ";
x2:
	int paatos;
	paatos = syoteTarkastus();


	if (paatos > 2 || paatos < 1) {
		cout << endl;

		cout << "Virheellinen valinta! Yrit� uudestaan." << endl;
		goto x2;

	}

	if (paatos == 1) {

		goto beginning;

	}

	else if (paatos == 2) {

		cout << endl;

	}

	cout << "Palataan p��valikkoon" << endl << endl;
	cout << "-------------------------------------------------------------------------------------" << endl << endl;

}




// Aliohjelma, jossa voidaan peruuttaa varauksia
// Aliohojelmaan l�hetet��n taulukko ja vapaat huoneet


void varauksenPeruutus(struct hotelli varaaja[], int& vapaatHuoneet) {
	setlocale(LC_ALL, "Finnish");
	int varausNumero;

	cout << endl;
	system("cls");

	cout << endl;
	cout << "Ole hyv� ja sy�t� varausnumerosi. " << endl;
	varausNumero = syoteTarkastus();

	bool testaaja3 = false;

	while (testaaja3 == false) {

		if (varausNumero < 1) {
			testaaja3 = false;
			cout << endl;
			cout << "Virheellinen valinta! Yrit� uudestaan." << endl << endl;
			cout << "Varausnumero ei voi olla pienempi kuin 1. " << endl;
			varausNumero = syoteTarkastus();


		}
		else {
			testaaja3 = true;
		}

	}

	cout << endl << endl;

	// Kun ohjelma on saanut varausnumeron, l�htee se suorittamaan looppia ja vertaamaan alkioiden arvoa varausnumeroon
	// Jos varausnumero t�sm�� alkion arvoon, se ilmoittaa asiasta k�ytt�j�lle ja peruuttaa varauksen muuttamalla alkion arvon takaisin nollaksi
	// Jos varaus my�s peruutetaan, niin ohjelma lis�� vapaiden huoneiden arvoksi yhden lis��

	bool testaaja2 = false;

	for (int i = 0; i < 300; i++) {

		if (varaaja[i].varausNro == varausNumero) {
			varaaja[i].varausNro = 0;
			varaaja[i].nimi = "---";
			vapaatHuoneet++;
			cout << "Varauksesi on nyt poistettu" << endl;
			cout << "Huoneita vapaana " << vapaatHuoneet << endl;
			testaaja2 = true;
			break;
		}


	}
	// Jos varausnumero ei vastaa mihnk��n alkioon, niin kysyt��n haluaako k�ytt�j� palata p��valikkoon vai sy�tt�� uuden varausnumeron
	// Jos k�ytt�j� haluaa sy�tt�� uuden numeron, niin ohjelma palautuu t�m�n aliohjelman alkuun suorittamaan uudestaan

	while (testaaja2 == false) {
		cout << "Numerolla ei l�ytynyt varauksia";
		cout << endl;
		testaaja2 = true;
	}

	cout << endl;
	cout << "Haluaisitko sy�tt�� uuden varausnumeron vai palata p��valikkoon? " << endl;
	cout << "1 = Sy�t� uusi varausnumero" << endl << "2 = Palaa p��valikkoon ";

	int paatos;

	paatos = syoteTarkastus();
	bool testaaja = false;

	while (testaaja == false) {

		if (paatos < 1 || paatos > 2) {
			testaaja = false;
			cout << endl;
			cout << "Virheellinen valinta! Yrit� uudestaan." << endl << endl;
			cout << "Haluaisitko sy�tt�� uuden varausnumeron vai palata p��valikkoon? " << endl;
			cout << "1 = Sy�t� uusi varausnumero" << endl << "2 = Palaa p��valikkoon ";
			paatos = syoteTarkastus();
		}
		else {
			testaaja = true;
		}

	}


	if (paatos == 1) {
		varauksenPeruutus(varaaja, vapaatHuoneet);
	}

	else if (paatos == 2) {
		return;
	}

}

void varausPeruutus_nimi(struct hotelli varaaja[], int& vapaatHuoneet) {

	setlocale(LC_ALL, "Finnish");
	string varaus_tarkastus;

	cout << endl;
	system("cls");

	cout << endl;
	cout << "Sy�t� nimesi: ";

	getline(cin, varaus_tarkastus);

	cout << endl << endl;

	// Kun ohjelma on saanut varausnumeron, l�htee se suorittamaan looppia ja vertaamaan alkioiden arvoa varausnumeroon
	// Jos varausnumero t�sm�� alkion arvoon, se ilmoittaa asiasta k�ytt�j�lle ja peruuttaa varauksen muuttamalla alkion arvon takaisin nollaksi
	// Jos varaus my�s peruutetaan, niin ohjelma lis�� vapaiden huoneiden arvoksi yhden lis��
	bool testi = false;
	for (int i = 0; i <= 300; i++) {

		if (varaaja[i].nimi == varaus_tarkastus) {
			varaaja[i].nimi = "---";
			varaaja[i].varausNro = 0;
			vapaatHuoneet++;
			cout << "Varauksesi huoneesta numero: " << i + 1 << " on nyt poistettu." << endl;
			cout << "Huoneita vapaana " << vapaatHuoneet << endl;
			testi = true;
			break;
		}
	}

	if (testi == false) {
		cout << "Nimell� ei l�ytynyt varauksia.";
		cout << endl;
	}

	// Jos varausnumero ei vastaa mihnk��n alkioon, niin kysyt��n haluaako k�ytt�j� palata p��valikkoon vai sy�tt�� uuden varausnumeron
	// Jos k�ytt�j� haluaa sy�tt�� uuden numeron, niin ohjelma palautuu t�m�n aliohjelman alkuun suorittamaan uudestaan

	cout << endl;
	cout << "Haluaisitko sy�tt�� uuden Nimen vai palata p��valikkoon? " << endl;
	cout << "1 = Sy�t� uusi Nimi" << endl << "2 = Palaa p��valikkoon ";

	int paatos;

	paatos = syoteTarkastus();

	bool testaaja = false;

	while (testaaja == false) {

		if (paatos < 1 || paatos > 2) {
			testaaja = false;
			cout << endl;
			cout << "Virheellinen valinta! Yrit� uudestaan." << endl << endl;
			cout << "Haluaisitko sy�tt�� uuden Nimen vai palata p��valikkoon? " << endl;
			cout << "1 = Sy�t� uusi Nimi" << endl << "2 = Palaa p��valikkoon ";
			paatos = syoteTarkastus();
		}
		else {
			testaaja = true;
		}

	}

	if (paatos == 1) {
		varausPeruutus_nimi(varaaja, vapaatHuoneet);
	}

	else if (paatos == 2) {

		return;
	}

}



/*Alihojelma, jossa voidaan tarkastaa kuinka monta huonetta on vapaana ja mitk� huoneet ovat varattuja*/

void tarkastaVapaat(struct hotelli varaaja[], int& vapaatHuoneet) {
	system("cls");
	cout << endl << endl;

	cout << "Huoneita vapaana: " << vapaatHuoneet << endl << endl;

	cout << "Huonenumerot, jotka ovat varattu: ";

	for (int i = 0; i < 300; i++) {
		varaaja[i];

		if (varaaja[i].varausNro > 0) {
			cout << i + 1 << ", ";
		}

	}
	cout << endl << endl;
	cout << "Jos haussa ei ilmene huoneita, silloin kaikki huoneet ovat vapaita.";
	cout << endl << endl;
	cout << "Paina jotain n�pp�int� p��st�ksesi takaisin p��valikkoon." << endl << endl;
	system("pause");
}



// Alihojelma, joka esitt�� hinnaston kutsuttaessa
void hinnasto(int huoneet) {
	setlocale(LC_ALL, "Finnish");
	system("cls");
	cout << "Hinnat ovat seuraavat:" << endl << endl;
	cout << "100 euroa ensimm�iselt� y�lt� ja 80 euroa siit� eteenp�in" << endl;
	cout << endl << endl;
	cout << "Paina jotain n�pp�int� p��st�ksesi takaisin p��valikkoon" << endl;
	cout << endl;
	system("Pause");										// Pys�ytet��n ohjelma, jotta k�ytt�j� ehtii lukemaan tiedot ja p��tt�m��n itse, milloin palaa p��valikkoon
	cout << endl << endl;


}

// Aliohjelma sy�tteen tarkastukselle

int syoteTarkastus() {

	int valinta = 0;
	cout << endl;
	cout << "sy�t� valintasi: ";
	cin >> setw(1) >> valinta;

	while (cin.good() == false)
	{

		cout << "Virheellinen valinta! Yrit� uudestaan..." << endl;

		cout << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');


		cout << "Sy�ta p��t�ksesi: ";
		cin >> setw(1) >> valinta;
		cout << endl;

	}

	cin.clear();										// Pyyhkii viel� viimeisen kerran sy�tteen, ennenkuin l�hett�� takaisin
	cin.ignore(INT_MAX, '\n');


	return valinta;

}
// Toinen sy�tteen tarkastuksen aliohjelma, jossa voidaan tarkastaa p��valikon sy�tteet erikseen
int syoteValikko() {

	int valinta = 0;
	cout << " Sy�ta valintasi  ";
	cin >> setw(1) >> valinta;


	while (cin.good() == false)
	{
		system("cls");

		cout << endl << endl;
		cout << "Virheellinen valinta! Yrit� uudestaan..." << endl << endl;
		cout << "----------------------------------------------------------------" << endl << endl;
		cout << "\t" << "TERVETULOA KARAMIN HOTELLIIN " << endl << endl;
		cout << "----------------------------------------------------------------" << endl << endl;

		cout << " Mit� haluaisit tehd�?" << endl << endl;



		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cout << " 1: Varaa huone" << endl;
		cout << " 2: tarkista hinnasto" << endl;
		cout << " 3: Tarkasta varaus varausnumerolla" << endl;
		cout << " 4: Tarkasta varaus nimell�" << endl;
		cout << " 5: Peruuta varaus varausnumerolla" << endl;
		cout << " 6: Peruuta varaus nimell�" << endl;
		cout << " 7: Tarkasta vapaana olevat huoneet" << endl;
		cout << " 8: poistu" << endl << endl;

		cout << " Sy�ta valintasi  ";
		cin >> setw(1) >> valinta;
		cout << endl;

	}

	// tyhjennet��n viel� kerran sy�te
	cin.clear();
	cin.ignore(INT_MAX, '\n');


	return valinta;
}


