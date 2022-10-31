#include<iostream>
#include<string>								// stringit käyttöön
#include<cmath>									// Otetaan matikka kirjasto käyttöön varmuuden varalta, jos on tarvetta
#include<ctime>									// Otetaan tietokoneen kello käyttöön
#include<iomanip>								// otetaan käyttöön kirjasto syötteen tarkastuksen tarkkuuteen.
#include<windows.h>

using namespace std;



// Creating a structure class for names and reservation numbers
struct hotelli {

	string nimi = " ";
	int varausNro = 0;

};

int syoteValikko();															// Luodaan aliohjelma, jossa voidaan valikolle tehdä oma tarkastus
int syoteTarkastus();														// Luodaan aliohjelma, jossa tarkistetaan syötteet
void hinnasto(int huoneet);													// Luodaan aliohjelma, jossa voidaa esittää hinnasto
void tarkastaVapaat(struct hotelli varaaja[], int& vapaatHuoneet);						// Luodaan aliohjelma, jossa voidaan tarkastaa varatut huoneet
void taulukot2(struct hotelli varaaja[], int& vapaatHuoneet);				// Luodaan alihjelma, jossa voidaan varata huoneita
void taulukot3(struct hotelli varaaja[], int& vapaatHuoneet);				// Luodaan aliohjelma jossa voidaan käsitellä jatkovarauksia
void varausTarkastus(struct hotelli varaaja[], int& vapaatHuoneet);			// Luodaan aliohjelma, jossa voidaan tarkastaa varatut huoneet
void varauksenPeruutus(struct hotelli varaaja[], int& vapaatHuoneet);		// Luodaan aliohjelma, jossa voidaan peruuttaa varauksia
void varausTarkastus_nimi(struct hotelli varaaja[], int& vapaatHuoneet);
void varausPeruutus_nimi(struct hotelli varaaja[], int& vapaatHuoneet);


const int huoneMaara = 300;							// Luodaan muutama globaali vakio huoneille ja hinnoille
const int hinta1 = 100;
const int hinta2 = 80;



int main() {
	SetConsoleCP(1252);							// Tällä komennolla saadaan myös käyttäjän syöttämät ääkköset näkyviin
												// Vaatii <windwos.h> kirjaston toimiakseen

	srand(time(0));								//Tällä komennolla saadaan varausnumero generoimaan aina uudet numerot
	setlocale(LC_ALL, "Finnish");

	hotelli varaaja[huoneMaara];
	int valinta;
	int vapaatHuoneet = 300;


	for (int i = 0; i < 300; i++) {
		varaaja[i].nimi = "---";
		varaaja[i].varausNro = 0;
	}

	do {
		system("cls");							// Tätä komentoa on ripoteltu välillä pyyhkimään konsolin, jotta se pysyy puhtaamman näköisenä

	p1:											// komento siis pyyhkii konsolin puhtaaksi
												// p1 palautuspiste.... Palautuspisteitä löytyy välillä vaihtamaan ohjelman suuntaa riippuen käyttäjän valinnoista
		cout << endl << endl;
		cout << "----------------------------------------------------------------" << endl << endl;
		cout << "\t" << "TERVETULOA KARAMIN HOTELLIIN " << endl << endl;
		cout << "----------------------------------------------------------------" << endl << endl;
		cout << " Mitä haluaisit tehdä?" << endl << endl;

		cout << " 1: Varaa huone" << endl;
		cout << " 2: tarkista hinnasto" << endl;
		cout << " 3: Tarkasta varaus varausnumerolla" << endl;
		cout << " 4: Tarkasta varaus nimellä" << endl;
		cout << " 5: Peruuta varaus varausnumerolla" << endl;
		cout << " 6: Peruuta varaus nimellä" << endl;
		cout << " 7: Tarkasta vapaana olevat huoneet" << endl;
		cout << " 8: poistu" << endl << endl;

		// Käyttäjän syöttö lähtee erilliseen aliohjelmaan tarkastamaan syöttöä ja palauttaa takaisin, jos syöte on hyväksytty
		valinta = syoteValikko();

		// toinen syötteen tarkastus, jos syötteeseen tulee väärä numeroarvo ohjelma palauttaa pisteeseen p1 ja lähtee suorittamaan uudestaan

		if (valinta < 1 || valinta > 8) {
			cout << endl;
			system("cls");
			cout << endl << endl;
			cout << "Virheellinen valinta! Yritä uudestaan...";
			goto p1;
		}


		else if (valinta == 1) {
			taulukot2(varaaja, vapaatHuoneet);					// lähdetään varamaan huoneita aliohjelmaan
		}

		else  if (valinta == 2) {
			hinnasto(valinta);												// kutsutaan hinnasto aliohjelmaa
		}

		else if (valinta == 3) {

			varausTarkastus(varaaja, vapaatHuoneet);				// Lähdetään tarkastamaan varauksia
		}

		else if (valinta == 4) {

			varausTarkastus_nimi(varaaja, vapaatHuoneet);						// Lähdetään peruuttamaan varauksia

		}


		else if (valinta == 5) {

			varauksenPeruutus(varaaja, vapaatHuoneet);						// Lähdetään peruuttamaan varauksia

		}

		else if (valinta == 6) {

			varausPeruutus_nimi(varaaja, vapaatHuoneet);						// Lähdetään peruuttamaan varauksia

		}

		else if (valinta == 7) {

			tarkastaVapaat(varaaja, vapaatHuoneet);


		}

	} while (valinta != 8); {												// Jos käyttäjä syöttää numeron 6, niin ohjelma lopettaa
		cout << endl;
		system("cls");
		cout << endl;
		cout << "************************************************" << endl << endl;
		cout << "Kiitos käynnistä ja Tervetuloa uudestaan!" << endl << endl;
		cout << "************************************************" << endl;
	}


}


// Alihojelma, jossa voidaan tehdä huonevarauksia
// Aliohjelmaan lähetetään taulukko ja vapaiden huoneiden määrä
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

	huoneVaraus = syoteTarkastus();												// Valinta lähtee syötteen tarkastukseen

	if (huoneVaraus < 1 || huoneVaraus > 300) {
		cout << "Virheellinen valinta! Yritä uudestaan..." << endl << endl;
		goto p2;

	}
	// Tarkastetaan onko huone vapaa. Jos valitun huoneen alkion arvo on suurempi kuin 0, ohjelma ilmoittaa huoneen olevan varattu
	// Mukana on myös palautus piste p2 joka lähettää ohjelman suorittamaan uudestaan, jos huone on varattu
	else if (varaaja[huoneVaraus - 1].varausNro > 0) {

		cout << endl << endl;
		cout << "Tämä huone on valitettavasti jo varattu" << endl << endl;
		goto p2;
	}
	// Jos huone on vapaa, niin silloin määritetään sen arvo generoidulla varausnumerolla, jotta se muuttuu varatuksi
	// Jos huone voidaan varata, pudotetaan vapaiden huoneiden määrää yhdellä
	else if (varaaja[huoneVaraus - 1].varausNro < 1) {

		vapaatHuoneet--;

		varaaja[huoneVaraus - 1].varausNro = (rand() % 90000) + 9999;

	}

	// pyydetään käyttäjältä vietetyt yöt, jotta voidaan laskea summa laskulle

	cout << "Montako yötä haluaisit viettää? ";
	paivat = syoteTarkastus();


	cout << endl;


	cout << "Syötä vielä koko nimesi: ";
	getline(cin, varaaja[huoneVaraus - 1].nimi);
	cout << endl;

	cout << "Kiitos! " << varaaja[huoneVaraus - 1].nimi << " Huoneesi on nyt varattu!" << endl << endl;
	cout << "Laskusi summa on: " << (paivat - 1) * hinta2 + hinta1 << " euroa, joka maksetaan kirjautumisen yhteydessä" << endl;		// lasketaan summa varaukselle
	cout << endl;
	cout << "Tämän huoneen varausnumero on: " << varaaja[huoneVaraus - 1].varausNro << endl << "(Varausnumerolla voit tarkastaa ja peruuttaa varauksia, pidä se siis tallessa)" << endl << endl;
p3:
	cout << "Huoneita vapaana: " << vapaatHuoneet << endl;

	cout << "Haluaisitko jatkaa varaamista? (1 = Kyllä 2 = Ei) ";
	int valinta2;
	valinta2 = syoteTarkastus();


	if (valinta2 < 1 || valinta2 > 2) {
		cout << endl;
		cout << "Virheellinen valinta! Yritä uudestaan" << endl << endl;
		goto p3;
	}



	// TÄSSÄ MENOSSA-------------------------------- 1.2.2022



	else if (valinta2 == 1) {						// Jos halutaan jatkaa varaamista, kutsutaan toista aliohjelmaa, jossa voidaan antaa uusia varausnumeroita
		taulukot3(varaaja, vapaatHuoneet);
	}

	else if (valinta2 == 2) {
		cout << "Selvä palataan päävalikkoon" << endl << endl;
		cout << "----------------------------------" << endl << endl;

	}

}

// Toinen aliohjelma, jossa voidaan tehdä jatkovarauksia huoneille
// Alihojelmaan lähetetään taulukko, vanha varausnumero ja vapaiden huoneiden määrä

void taulukot3(struct hotelli varaaja[], int& vapaatHuoneet) {
	setlocale(LC_ALL, "Finnish");
	int huoneVaraus;
	string nimi;

	cout << endl << endl;
	system("cls");
p2:
	cout << "Huoneita vapaana: " << vapaatHuoneet << endl;
	cout << "Minkä huoneen haluaisit varata? (1-300) ";

	huoneVaraus = syoteTarkastus();


	if (huoneVaraus < 1 || huoneVaraus > 300) {
		cout << "Virheellinen valinta! Yritä uudestaan..." << endl << endl;
		goto p2;

	}
	// Tarkastetaan onko huone vapaa. Jos valitun huoneen alkion arvo on suurempi kuin 0, ohjelma ilmoittaa huoneen olevan varattu
	// Mukana on myös palautus piste p2 joka lähettää ohjelman suorittamaan uudestaan, jos huone on varattu
	else if (varaaja[huoneVaraus - 1].varausNro > 0) {

		cout << endl << endl;
		cout << "Tämä huone on valitettavasti jo varattu" << endl << endl;
		goto p2;
	}
	// Jos huone on vapaa, niin silloin määritetään sen arvo 1, jotta se muuttuu varatuksi
	// Pudotetaan myös vapaiden huoneiden määrää
	else if (varaaja[huoneVaraus - 1].varausNro == 0) {
		vapaatHuoneet--;
		varaaja[huoneVaraus - 1].varausNro = (rand() % 90000) + 9999;
	}

	// pyydetään käyttäjältä vietetyt yöt, jotta voidaan laskea summa laskulle

	cout << "Montako yötä haluaisit viettää? ";
	int paivat;
	paivat = syoteTarkastus();

	cout << endl;

	cout << "Syötä vielä koko nimesi: ";
	getline(cin, varaaja[huoneVaraus - 1].nimi);
	cout << endl;


	//Määritetään varatun huoneen alkio varausnumeroksi, jotta voidaan myöhemmin hakea varauksia numeroilla	


	cout << "Kiitos! " << varaaja[huoneVaraus - 1].nimi << " Huoneesi on nyt varattu!" << endl << endl;
	cout << "Laskusi summa on: " << (paivat - 1) * hinta2 + hinta1 << " euroa, joka maksetaan kirjautumisen yhteydessä" << endl;		// lasketaan summa varaukselle

	cout << "Tämän huoneen varausnumero on: " << varaaja[huoneVaraus - 1].varausNro << endl << "(Varausnumerolla voit tarkastaa ja peruuttaa varauksia, pidä se siis tallessa)" << endl << endl;

p3:
	cout << "Huoneita vapaana: " << vapaatHuoneet << endl;
	cout << "Haluaisitko jatkaa varaamista? (1 = Kyllä 2 = Ei) ";
	int valinta2;
	valinta2 = syoteTarkastus();


	if (valinta2 < 1 || valinta2 > 2) {					// Jos tulee virheellinen syöttö, palautetaan pisteeseen p3
		cout << endl;
		cout << "Virheellinen valinta! Yritä uudestaan.";
		cout << endl << endl;
		goto p3;
	}

	else if (valinta2 == 1) {							// Jos käyttäjä haluaa jatkaa varaamista, lähdetään suorittamaan tätä aliohjelmaa uudestaan
		goto p2;										// Eli palautetaan pisteeseen p2, joka on alihojelman alussa
	}

	else if (valinta2 == 2) {								// Jos ei haluta jatkaa varaamista, annetaan aliohjelman palata takaisin pääohjelmaan

		cout << endl;
		cout << "Selvä! Palataan takaisin valikkoon!" << endl << endl;
		cout << "---------------------------------------------------------" << endl << endl;
	}

}

// Alihojelma, jossa voidaan tarkastaa varauksia
// Alihojelmaan lähetetään taulukko, varausnumero ja vapaat huoneet
void varausTarkastus(struct hotelli varaaja[], int& vapaatHuoneet) {
	setlocale(LC_ALL, "Finnish");
	int varausNroTarkistus;

	cout << endl << endl;
	system("cls");
p1:
	cout << endl;

	cout << "Syötä varausnumerosi: " << endl;

	varausNroTarkistus = syoteTarkastus();



	cout << endl << endl;

	if (varausNroTarkistus == 0) {
		cout << "Virheellinen valinta. Yritä uudestaan.";
		goto p1;
	}


	// Kun käyttäjä on syöttänyt varausnumeron, ohjelma lähtee suorittamaan loopin ja vertaamaan alkioiden arvoja
	// Jos looppi löytää alkion, jonka arvo vastaa varausnumeroa looppi breakkaa ja hyppää seuraavaan ilmoitettuun pisteeseen
	// Jos ei löydä, niin ohjelma ilmoittaa asiasta ja kysyy haluaako käyttäjä syöttää uuden numeron
	for (int i = 0; i < 300; i++) {
		if (varaaja[i].varausNro == varausNroTarkistus) {

			cout << "Tällä numerolla löytyy varaus järjestelmästä." << endl << "Varatun huoneen numero: " << i + 1;
			cout << endl << endl;
			goto x1;
			break;

		}


	}

	cout << "Numerolla ei löytynyt varausta järjestelmästä." << endl << endl;
x1:
	// Ohjelma kysyy, haluaako käyttäjä antaa uuden numeron
	// Jos käyttäjä haluaa, niin ohjelma palaa tämän alihojelman alkuun
	// Jos ei, niin aliohjelma palautuu pääohjelmaan
	cout << "Haluaisitko syöttää uuden varausnumeron vai palata päävalikkoon? " << endl;
	cout << "1 = Syötä uusi varausnumero" << endl << "2 = Palaa päävalikkoon ";
x2:
	int paatos;
	paatos = syoteTarkastus();


	if (paatos > 2 || paatos < 1) {
		cout << endl;

		cout << "Virheellinen valinta! Yritä uudestaan." << endl;
		goto x2;

	}

	if (paatos == 1) {

		goto p1;

	}

	else if (paatos == 2) {

		cout << endl;

	}

	cout << "Palataan päävalikkoon" << endl << endl;
	cout << "-------------------------------------------------------------------------------------" << endl << endl;
}
/*Aliohelma, jossa voidaan tarkastaa varaukset käyttämällä nimeä*/

void varausTarkastus_nimi(struct hotelli varaaja[], int& vapaatHuoneet) {
	setlocale(LC_ALL, "Finnish");
	string varaus_tarkastus;

	cout << endl << endl;
	system("cls");
beginning:

	cout << endl;

	cout << "Syötä nimesi: ";

	getline(cin, varaus_tarkastus);

	cout << endl << endl;

	// Kun käyttäjä on syöttänyt varausnumeron, ohjelma lähtee suorittamaan loopin ja vertaamaan alkioiden arvoja
	// Jos looppi löytää alkion, jonka arvo vastaa varausnumeroa looppi breakkaa ja hyppää seuraavaan ilmoitettuun pisteeseen
	// Jos ei löydä, niin ohjelma ilmoittaa asiasta ja kysyy haluaako käyttäjä syöttää uuden numeron
	bool testi = false;
	for (int i = 0; i < 300; i++) {
		if (varaaja[i].nimi == varaus_tarkastus) {

			cout << "Tällä nimellä löytyy varaus järjestelmästä." << endl << "Varatun huoneen numero: " << i + 1;
			cout << endl << endl;
			testi = true;

		}

	}
	if (testi == false) {
		cout << "Tällä nimellä ei löytynyt varausta järjestelmästä. " << endl << endl;
	}


x1:
	// Ohjelma kysyy, haluaako käyttäjä antaa uuden numeron
	// Jos käyttäjä haluaa, niin ohjelma palaa tämän alihojelman alkuun
	// Jos ei, niin aliohjelma palautuu pääohjelmaan
	cout << "Haluaisitko syöttää uuden nimen vai palata päävalikkoon? " << endl;
	cout << "1 = Syötä uusi nimi" << endl << "2 = Palaa päävalikkoon ";
x2:
	int paatos;
	paatos = syoteTarkastus();


	if (paatos > 2 || paatos < 1) {
		cout << endl;

		cout << "Virheellinen valinta! Yritä uudestaan." << endl;
		goto x2;

	}

	if (paatos == 1) {

		goto beginning;

	}

	else if (paatos == 2) {

		cout << endl;

	}

	cout << "Palataan päävalikkoon" << endl << endl;
	cout << "-------------------------------------------------------------------------------------" << endl << endl;

}




// Aliohjelma, jossa voidaan peruuttaa varauksia
// Aliohojelmaan lähetetään taulukko ja vapaat huoneet


void varauksenPeruutus(struct hotelli varaaja[], int& vapaatHuoneet) {
	setlocale(LC_ALL, "Finnish");
	int varausNumero;

	cout << endl;
	system("cls");

	cout << endl;
	cout << "Ole hyvä ja syötä varausnumerosi. " << endl;
	varausNumero = syoteTarkastus();

	bool testaaja3 = false;

	while (testaaja3 == false) {

		if (varausNumero < 1) {
			testaaja3 = false;
			cout << endl;
			cout << "Virheellinen valinta! Yritä uudestaan." << endl << endl;
			cout << "Varausnumero ei voi olla pienempi kuin 1. " << endl;
			varausNumero = syoteTarkastus();


		}
		else {
			testaaja3 = true;
		}

	}

	cout << endl << endl;

	// Kun ohjelma on saanut varausnumeron, lähtee se suorittamaan looppia ja vertaamaan alkioiden arvoa varausnumeroon
	// Jos varausnumero täsmää alkion arvoon, se ilmoittaa asiasta käyttäjälle ja peruuttaa varauksen muuttamalla alkion arvon takaisin nollaksi
	// Jos varaus myös peruutetaan, niin ohjelma lisää vapaiden huoneiden arvoksi yhden lisää

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
	// Jos varausnumero ei vastaa mihnkään alkioon, niin kysytään haluaako käyttäjä palata päävalikkoon vai syöttää uuden varausnumeron
	// Jos käyttäjä haluaa syöttää uuden numeron, niin ohjelma palautuu tämän aliohjelman alkuun suorittamaan uudestaan

	while (testaaja2 == false) {
		cout << "Numerolla ei löytynyt varauksia";
		cout << endl;
		testaaja2 = true;
	}

	cout << endl;
	cout << "Haluaisitko syöttää uuden varausnumeron vai palata päävalikkoon? " << endl;
	cout << "1 = Syötä uusi varausnumero" << endl << "2 = Palaa päävalikkoon ";

	int paatos;

	paatos = syoteTarkastus();
	bool testaaja = false;

	while (testaaja == false) {

		if (paatos < 1 || paatos > 2) {
			testaaja = false;
			cout << endl;
			cout << "Virheellinen valinta! Yritä uudestaan." << endl << endl;
			cout << "Haluaisitko syöttää uuden varausnumeron vai palata päävalikkoon? " << endl;
			cout << "1 = Syötä uusi varausnumero" << endl << "2 = Palaa päävalikkoon ";
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
	cout << "Syötä nimesi: ";

	getline(cin, varaus_tarkastus);

	cout << endl << endl;

	// Kun ohjelma on saanut varausnumeron, lähtee se suorittamaan looppia ja vertaamaan alkioiden arvoa varausnumeroon
	// Jos varausnumero täsmää alkion arvoon, se ilmoittaa asiasta käyttäjälle ja peruuttaa varauksen muuttamalla alkion arvon takaisin nollaksi
	// Jos varaus myös peruutetaan, niin ohjelma lisää vapaiden huoneiden arvoksi yhden lisää
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
		cout << "Nimellä ei löytynyt varauksia.";
		cout << endl;
	}

	// Jos varausnumero ei vastaa mihnkään alkioon, niin kysytään haluaako käyttäjä palata päävalikkoon vai syöttää uuden varausnumeron
	// Jos käyttäjä haluaa syöttää uuden numeron, niin ohjelma palautuu tämän aliohjelman alkuun suorittamaan uudestaan

	cout << endl;
	cout << "Haluaisitko syöttää uuden Nimen vai palata päävalikkoon? " << endl;
	cout << "1 = Syötä uusi Nimi" << endl << "2 = Palaa päävalikkoon ";

	int paatos;

	paatos = syoteTarkastus();

	bool testaaja = false;

	while (testaaja == false) {

		if (paatos < 1 || paatos > 2) {
			testaaja = false;
			cout << endl;
			cout << "Virheellinen valinta! Yritä uudestaan." << endl << endl;
			cout << "Haluaisitko syöttää uuden Nimen vai palata päävalikkoon? " << endl;
			cout << "1 = Syötä uusi Nimi" << endl << "2 = Palaa päävalikkoon ";
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



/*Alihojelma, jossa voidaan tarkastaa kuinka monta huonetta on vapaana ja mitkä huoneet ovat varattuja*/

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
	cout << "Paina jotain näppäintä päästäksesi takaisin päävalikkoon." << endl << endl;
	system("pause");
}



// Alihojelma, joka esittää hinnaston kutsuttaessa
void hinnasto(int huoneet) {
	setlocale(LC_ALL, "Finnish");
	system("cls");
	cout << "Hinnat ovat seuraavat:" << endl << endl;
	cout << "100 euroa ensimmäiseltä yöltä ja 80 euroa siitä eteenpäin" << endl;
	cout << endl << endl;
	cout << "Paina jotain näppäintä päästäksesi takaisin päävalikkoon" << endl;
	cout << endl;
	system("Pause");										// Pysäytetään ohjelma, jotta käyttäjä ehtii lukemaan tiedot ja päättämään itse, milloin palaa päävalikkoon
	cout << endl << endl;


}

// Aliohjelma syötteen tarkastukselle

int syoteTarkastus() {

	int valinta = 0;
	cout << endl;
	cout << "syötä valintasi: ";
	cin >> setw(1) >> valinta;

	while (cin.good() == false)
	{

		cout << "Virheellinen valinta! Yritä uudestaan..." << endl;

		cout << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');


		cout << "Syöta päätöksesi: ";
		cin >> setw(1) >> valinta;
		cout << endl;

	}

	cin.clear();										// Pyyhkii vielä viimeisen kerran syötteen, ennenkuin lähettää takaisin
	cin.ignore(INT_MAX, '\n');


	return valinta;

}
// Toinen syötteen tarkastuksen aliohjelma, jossa voidaan tarkastaa päävalikon syötteet erikseen
int syoteValikko() {

	int valinta = 0;
	cout << " Syöta valintasi  ";
	cin >> setw(1) >> valinta;


	while (cin.good() == false)
	{
		system("cls");

		cout << endl << endl;
		cout << "Virheellinen valinta! Yritä uudestaan..." << endl << endl;
		cout << "----------------------------------------------------------------" << endl << endl;
		cout << "\t" << "TERVETULOA KARAMIN HOTELLIIN " << endl << endl;
		cout << "----------------------------------------------------------------" << endl << endl;

		cout << " Mitä haluaisit tehdä?" << endl << endl;



		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cout << " 1: Varaa huone" << endl;
		cout << " 2: tarkista hinnasto" << endl;
		cout << " 3: Tarkasta varaus varausnumerolla" << endl;
		cout << " 4: Tarkasta varaus nimellä" << endl;
		cout << " 5: Peruuta varaus varausnumerolla" << endl;
		cout << " 6: Peruuta varaus nimellä" << endl;
		cout << " 7: Tarkasta vapaana olevat huoneet" << endl;
		cout << " 8: poistu" << endl << endl;

		cout << " Syöta valintasi  ";
		cin >> setw(1) >> valinta;
		cout << endl;

	}

	// tyhjennetään vielä kerran syöte
	cin.clear();
	cin.ignore(INT_MAX, '\n');


	return valinta;
}


