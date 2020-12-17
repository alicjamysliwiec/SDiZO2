#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ratio>
#include <Windows.h>
#include <conio.h>


using namespace std;
#define KOLOR_NORMALNY SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY  | FOREGROUND_GREEN)

//funkcja 
void nacisnij()
{
	char a;
	fflush(stdin);
	cout << "Nacisnij dowolny klawisz aby kontynuowac\n";
	a = _getch();
}

//funkcja pobierajaca aktualny czas
LARGE_INTEGER getTime()
{
	LARGE_INTEGER time;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&time);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return time;
}

//struktura element reprezentujaca krawedz na liscie
struct Element {
	Element *nastepny; //wskaznik na nastêpny element
	int wierzcholek1; //wierzcholek, z ktorego wychodzi krawedz
	int wierzcholek2; //wierzcholek, do ktorego wchodzi krawedz
	int waga; //wartosc elementu

	//konstruktor - domyœlnie wszystkie wartoœci ustawiamy na zero
	Element(){
		nastepny = NULL;  
		wierzcholek1 = 0;
		wierzcholek2 = 0;
		waga = 0;
	};

	//konstruktor tworzacy element o zadanych wierzcholkach i wadze
	Element(int w1, int w2, int waga){
		nastepny = NULL;  //domyœlnie wszystkie wartoœci ustawiamy na zero
		this -> wierzcholek1 = w1;
		this -> wierzcholek2 = w2;
		this->waga = waga;
	};

};
//Klasa reprezentujaca liste
class Lista{
public:
	//konstruktor listy
	Lista(){
		Lista::poczatek = NULL; //domyœlnie ustawiamy pierwszy element na zero
	};
	//destruktor listy
	~Lista()
	{
		Element *element; //tworzymy wskaznik na element
		while(poczatek){  //dopoki jest element pocz¹tkowy
			element = poczatek->nastepny; //przechodzimy do kolejnego elementu listy
			delete[]poczatek;			  //usuwamy poprzedni element
		poczatek = element;			  //ustawiamy nowy poczatek listy
		}
	};					
	Element *poczatek;						//wskaznik na pierwszy element listy
	
	//funkcja dodajaca element do listy sortujaca wedlug wierzcholka docelowego (najnizsze na poczatku)
	void dodajW2(Element k){
		if (poczatek == NULL){                // je¿eli nie istnieje pierwszy element
			poczatek = new Element;			  // tworzymy nowy i ustawiamy jako pierwszy
			poczatek->waga = k.waga;		  // przypisujemy podane wartosci
			poczatek->wierzcholek1 = k.wierzcholek1;
			poczatek->wierzcholek2 = k.wierzcholek2;
		}
		else{
			Element *nowy = new Element;     //tworzymy nowy element
			nowy->waga = k.waga;			// przypisujemy podane wartosci
			nowy->wierzcholek1 = k.wierzcholek1;
			nowy->wierzcholek2 = k.wierzcholek2;

			if (poczatek->wierzcholek2 > nowy->wierzcholek2) //sprawdzamy czy wstawic na poczatku
			{
				nowy->nastepny = poczatek; //wstawiamy na poczatku listy
				poczatek = nowy;
			}
			else
			{
				Element *tmp = poczatek;
				while (tmp->nastepny != NULL) //przechodzimy dopoki nie napotkamy konca
				{
					if (tmp->nastepny->wierzcholek2 > nowy->wierzcholek2) break; //lub gdy wierzcholek nastepnego bedzie nizszy od wierzcholka dodawanego elementu
					tmp = tmp->nastepny; //przechodzimy do kolejnego elementu listy

				}

				nowy->nastepny = tmp->nastepny; //wstawiamy do listy
				tmp->nastepny = nowy;
			}
		}
	};

	// dodaj element na poczatek listy
	void dodaj(Element k){
		if (poczatek == NULL){                // je¿eli nie istnieje pierwszy element
			poczatek = new Element;			  // tworzymy nowy i ustawiamy jako pierwszy
			poczatek->waga = k.waga;		  // przypisujemy podane wartosci
			poczatek->wierzcholek1 = k.wierzcholek1;
			poczatek->wierzcholek2 = k.wierzcholek2;
		}
		else{
			Element *nowy = new Element;     //tworzymy nowy element
			nowy->waga = k.waga;		  // przypisujemy podane wartosci
			nowy->wierzcholek1 = k.wierzcholek1;		
			nowy->wierzcholek2 = k.wierzcholek2;		  
			nowy->nastepny = poczatek; //wstawiamy do listy
			poczatek = nowy;
		}
	};
	// dodaj i posortuj wedlug wagi
	void dodajWaga(Element k){
		if (poczatek == NULL){                // je¿eli nie istnieje pierwszy element
			poczatek = new Element;			  // tworzymy nowy i ustawiamy jako pierwszy
			poczatek->waga = k.waga;		 // przypisujemy podane wartosci
			poczatek->wierzcholek1 = k.wierzcholek1;
			poczatek->wierzcholek2 = k.wierzcholek2;
		}
		else{
			Element *nowy = new Element;     //tworzymy nowy element
			nowy->waga = k.waga;		  // przypisujemy podane wartosci
			nowy->wierzcholek1 = k.wierzcholek1;
			nowy->wierzcholek2 = k.wierzcholek2;

			if (poczatek->waga > nowy->waga) //sprawdzamy czy wstawic na poczatku
			{
				nowy->nastepny = poczatek; //wstawiamy na poczatku listy
				poczatek = nowy;
			}
			else
			{
				Element *tmp = poczatek;
				while (tmp->nastepny != NULL) //przechodzimy dopoki nie napotkamy konca
				{
					if (tmp->nastepny->waga > nowy->waga) break; //lub gdy waga nastepnego bedzie nizszy od wagi dodawanego elementu
					tmp = tmp->nastepny;

				}
				nowy->nastepny = tmp->nastepny; //wstawiamy do listy
				tmp->nastepny = nowy;
			}
		}
	};
	void usunPierwszy(){
		if (poczatek == NULL) cout << "Lista jest pusta\n";	//Je¿eli nie istnieje pierwszy element, to lista jest pusta
		else
		{
			Element *e = poczatek->nastepny; //Ustawienie elementu e jako nowego pierwszego
			delete poczatek; //usuwamy poczatek
			poczatek = e; // ustawiamy nowy poczatek
		}
	}
	// funkcja zwracajaca wskaznik na poczatek listy
	Element *getPoczatek()
	{
		return poczatek;
	};
	//funkcja zwracajaca rozmiar struktury
	int getSize(){
		if (poczatek == NULL) return 0; // jesli nie ma poczatku wroc 0
		else
		{
			int n = 1; //ustawiamy licznik na 1
			Element *tmp = poczatek;
			while (tmp->nastepny != NULL) // sprawdzamy czy istnieje nastepny element
			{
				n++; //zwiekszamy licznik
				tmp = tmp->nastepny; //przechodzimy do nastepnego
			}
			return n;
		}
	};

	//funkcja wyswietlajaca drzewo MST
	void wyswietlMST()
	{
		Element *tmp = poczatek; // ustawiamy wskaznik na poczatek tablicy
		int waga = 0; //ustawiamy wage na 0
		while (tmp != NULL) //sprawdzamy czy istnieje kolejny element
		{
			waga += tmp->waga; //zwiekszamy wage
			cout << tmp->wierzcholek1 << " -> " << tmp->wierzcholek2 << " = " << tmp->waga << endl; // wypisujemy elemnt listy
			tmp = tmp->nastepny; //przechodzimy do nastepnej krawedzi
		}
		cout << "Minimalne drzewo rozpinajace ma wage: " << waga << endl; //wypisujemy wage drzewa
	
	}
};

//funkcja wypisujaca droge do zadanego wierzcholka na podstawie tablicy obciazenia i poprzednik oraz liczby wierzcholkow
void wypiszDrogeDoWierzcholka(int *obciazenie, int *poprzednik, int wierzcholki, int wierzcholek)
{
	int tmp = wierzcholek; //zapisujemy wierzcholek poczatkowy
	int obc = obciazenie[wierzcholek]; // zapisujemy obciazenie
	if (tmp<10 && wierzcholki>10) cout << " ";
	cout << tmp; // wypisujemy aktaulny wierzcholek
	tmp = poprzednik[tmp]; //ustawiamy wierzcholek na jego poprzednika
	while (tmp != -1) //dopoki nie trafimy na korzen
	{
		cout << " <- " << tmp;
		if (tmp<10 && wierzcholki>10) cout << " ";
		tmp = poprzednik[tmp]; //przechodzimy do poprzednika
	}
	cout << " : " << obc << endl; // wypisujemy obciazenie

}

//funkcja wypisujaca droge do wszystkich wierzcholkow na podstawie tablicy obciazenia i poprzednik oraz liczby wierzcholkow
void wypisz(int *obciazenie, int *poprzednik, int wierzcholki)
{
	for (int i = 0; i < wierzcholki; i++) //dla kazdego wierzcholka wywolujemy funkcje wypisujac
	{
		wypiszDrogeDoWierzcholka(obciazenie, poprzednik, wierzcholki, i);
	}
}

//klasa reprezentujaca liste sasiadow
class ListaSasiadow{
public:
	int wierzcholki; //liczba wierzcholkow
	//funkcja dodajaca krawedz do wierzcholka, jesli graf jest skierowany
	void dodajKrawedz(int v1, int v2, int value, bool skierowany){
		tab[v1].dodajW2(Element(v1, v2, value));
		if (!skierowany) 
		{
			tab[v2].dodajW2(Element(v2, v1, value));
		}
	}
	Lista *tab; //tablica List
	//konstruktor tworzacy liste o wielkosci liczby wierzcholkow
	ListaSasiadow(int w){
		wierzcholki = w;
		tab = new Lista[wierzcholki];
	}
	//funkcja wyswietlajca liste Sasiadow
	void wyswietl(){
	Element *temp;

	for (int i = 0; i<wierzcholki; i++) //dla kazdego wierzcholka
	{
		if (wierzcholki>10 && i < 10) cout << " ";
		cout << i << ":";
		temp = tab[i].poczatek;
		while (temp != NULL) //wypisujemy liste
		{
			if (temp->wierzcholek2 < 10) cout << " ";
			cout << " " << temp->wierzcholek2 << "->" << temp->waga;
			if (temp->waga < 10) cout << " ";

			if (temp->nastepny == NULL)
				temp = NULL;
			else temp=temp->nastepny; //przechodzimy do nastepnej krawedzi
		}
		cout << endl;
	}
	};


	//funkcja wywolujaca algorytm Kruskala dla reprezentacji listy sasiadow zwracajca czas dzialania algorytmu, domyslnie wyswietlajaca wynik
	LARGE_INTEGER Kruskal_list(bool wyp=true)
	{
		LARGE_INTEGER start, koniec, tm;
		start = getTime(); //pobranie czasu
		Element *tmp;
		Lista tab2; //tablica wszystkich krawedzi
		Lista rozwiazanie; //tablica zawierajaca rozwiazanie
		int liczbaGrafow = wierzcholki; //liczba roznych grafow
		int *tabGrafow; //tabela grafow
		tabGrafow = new int[wierzcholki];

		//dodawanie krawedzi do tablicy wszystkich krawedzi i sortowanie ich wedlug wagi
		for (int g = 0; g < wierzcholki; g++) //dla kazdego wierzcholka
		{
			tmp = tab[g].getPoczatek(); //ustawiamy wskaznik na poczatek listy
			while (tmp != NULL) //dopoki istnieje
			{
				tab2.dodajWaga(*tmp); //dodajemy element sortujac go wedlug wagi
				tmp = tmp->nastepny; // przechodzimy do nastepnego grafu
			}
			tabGrafow[g] = g; //ustawiamy kazdemu wierzcholkowi numer kolejnego grafu
		}

		while (liczbaGrafow != 1) //dopoki liczba grafow jest rozna od 1
		{
			tmp = tab2.getPoczatek(); //pobieramy pierwszy element z posortowanej listy
			if (tabGrafow[tmp->wierzcholek1] != tabGrafow[tmp->wierzcholek2]) //sprawdzamy czy wierzcholki krawedzi naleza do tego samego grafu
			{
				rozwiazanie.dodaj(*tmp); //dodajemy rozwiazanie do listy rozwiazan
				int tmpW = tabGrafow[tmp->wierzcholek2]; //zapisujemy numer grafu drugiego wierzcholka
				for (int i = 0; i < wierzcholki; i++) //dla kazdego wierzcholka 
				{
					if (tabGrafow[i] == tmpW) tabGrafow[i] = tabGrafow[tmp->wierzcholek1]; //zmieniamy numer grafu drugiego wierzcholka na nuumer grafu pierwszego wierzcholka
				}
				liczbaGrafow--; //zmniejszamy liczbe grafow

			}
			tab2.usunPierwszy(); //usuwamy pierwszy element na liscie
		}
		koniec = getTime();
		if (wyp)
		{
			cout << "Kruskal-Listowo" << endl;
			rozwiazanie.wyswietlMST();
		}

		delete[]tabGrafow;
		tm.QuadPart = koniec.QuadPart - start.QuadPart;
		return tm;
	}

	//funkcja wywolujaca algorytm Prima dla reprezentacji listy sasiadow zwracajca czas dzialania algorytmu, domyslnie wyswietlajaca wynik
	LARGE_INTEGER Prima_list(bool wyp=true)
	{
		LARGE_INTEGER start, koniec, tm;
		start = getTime(); //pobranie czasu
		Element *tmp;
		Lista tab2; //lista zawierajaca posortowana kolejke dostepnych krawedzi
		Lista rozwiazanie; //lista zawierajaca rozwiazanie
		bool *tabGrafow; //tabela czy wierzcholek nalezy do grafu
		tabGrafow = new bool[wierzcholki];
		for (int g = 0; g < wierzcholki; g++)
		{
			tabGrafow[g] = false; //ustawiamy domyslnie, ze wierzcholek nie nalezy
		}

		//wylosuj wierzcholek
		int poczatek = rand() % wierzcholki;
		tmp=tab[poczatek].getPoczatek();  //ustawiamy wskaznik na poczatek listy krawedzi wychodzacych z wierzcholkow
		tabGrafow[poczatek] = true; //dodajemy wierzcholek do grafu
		while (tmp != NULL) //dopoki element istnieje
		{
			tab2.dodajWaga(*tmp); //dodajemy element do listy i sortujemy wedlug wagi
			tmp = tmp->nastepny; //przechodzimy do kolejnej krawedzi
		}
		while (tab2.getSize() != 0) //dopoki lista krawedzi nie jest pusta
		{
			tmp = tab2.getPoczatek(); //pobieramy pierwszy elemnt z listy
			if (!tabGrafow[tmp->wierzcholek2]) //sprawdzamy czy wierzcholek docelowy nalezy do utworzonego juz grafu
			{
				tabGrafow[tmp->wierzcholek2] = true; //dodajemy wierzcholek do listy
				rozwiazanie.dodaj(*tmp); //dodajemy krawedz do rozwiazania
				tmp = tab[tmp->wierzcholek2].getPoczatek(); //pobieramy wierzcholek dla ktorego bedziemy sprawdzac krawedzie
				tab2.usunPierwszy(); //usuwamy pierwszy elemnt z listy
				while (tmp != NULL) //dopoki element istnieje
				{
					if (!tabGrafow[tmp->wierzcholek2]) tab2.dodajWaga(*tmp); //jesli wierzcholek nie nalezy do grafu to dodajemy krawedz do listy i sortujemy wedlug wagi
					tmp = tmp->nastepny; //przechodzimy do nastepnego elementu
				}
			}
			else
				tab2.usunPierwszy(); //usuwamy pierwszy elemnt z listy
			

		}

		koniec = getTime();
		if (wyp)
		{
			cout << "Prim-Listowo" << endl;
			rozwiazanie.wyswietlMST();
		}

		delete[]tabGrafow;
		tm.QuadPart = koniec.QuadPart - start.QuadPart;
		return tm;
	}
	//funkcja wywolujaca algorytm Dijkstry dla reprezentacji listy sasiadow zwracajca czas dzialania algorytmu, od poczatku do celu, domyslnie wyswietlajaca wynik
	LARGE_INTEGER Dijkstry_list(int poczatek, int cel, bool wyp=true)
	{
		LARGE_INTEGER start, koniec, tm;
		start = getTime(); //pobranie czasu startu algorytmu
		Element *tmp;
		Lista tab2; //posortowana lista krawdedzi
		bool *czy_sprawdzony; //tablica pokazujaca czy wierzcholek zostal sprawdzony (domyslnie false)
		czy_sprawdzony = new bool[wierzcholki];
		int *poprzednik; //tablica poprzednikow (domyslnie -1)
		poprzednik = new int[wierzcholki];
		int *obciazenie; //tablica obciazenia (domyslnie INT_MAX)
		obciazenie = new int[wierzcholki];
		int obc = INT_MAX; //zmienna przechowujaca aktualne obciazenie (domyslnie INT_MAX)

		for (int g = 0; g < wierzcholki; g++) //ustawienie wartosci w tabelach
		{
			czy_sprawdzony[g] = false;
			poprzednik[g] = -1;
			obciazenie[g] = INT_MAX;
		}
		obciazenie[poczatek] = 0; //ustawiamy obciazenie poczatku na 0

		for (int i = 0; i < wierzcholki; i++)
		{
			tmp = tab[poczatek].getPoczatek(); //pobieramy wskaznik na poczatek listy sasiedztwo aktualnie sprawdzanego wierzcholka
			while (tmp != NULL) //tworzenie listy krawedzi posortowanej wedlug wagi
			{
				if (!czy_sprawdzony[tmp->wierzcholek2]) tab2.dodajWaga(*tmp);
				tmp = tmp->nastepny;
			}
			while (tab2.getSize() != 0) //dopoki rozmiar listy krawedzi nie jest pusta
			{
				tmp = tab2.getPoczatek(); //pobieramy wskaznik na poczatek listy
				if (obciazenie[tmp->wierzcholek2] > obciazenie[tmp->wierzcholek1] + tmp->waga) //sprawdzamy czy droga z tego wierzcholka do danego wierzcholka jest krotsza niz wczesniej znaleziona
				{
					obciazenie[tmp->wierzcholek2] = obciazenie[tmp->wierzcholek1] + tmp->waga; //przepisanie nowoodkrytej drogi
					poprzednik[tmp->wierzcholek2] = tmp->wierzcholek1;
				}
				tab2.usunPierwszy(); //usuniecie pierwszego elemntu listy
			}
			czy_sprawdzony[poczatek] = true; //dodanie wierzcholka do sprawdzonych
			obc = INT_MAX;
			for (int j = 0; j < wierzcholki; j++) //szukanie najmniej obciazonego wierzcholka jeszcze nie sprawdzonego
			{
				if (obc > obciazenie[j] && !czy_sprawdzony[j])
				{
					obc = obciazenie[j];
					poczatek = j;
				}
			}
		}

		koniec = getTime();
		if (wyp)
		{
			cout << "Dijkstry-Listowo" << endl;
			if (cel == -1)
			{
				wypisz(obciazenie, poprzednik, wierzcholki);
			}
			else wypiszDrogeDoWierzcholka(obciazenie, poprzednik, wierzcholki, cel);
		}

		delete[]obciazenie;
		delete[]czy_sprawdzony;
		delete[]poprzednik;
		tm.QuadPart = koniec.QuadPart - start.QuadPart;
		return tm;
	}

	//funkcja wywolujaca algorytm Bellmana Forda dla reprezentacji listy sasiadow zwracajca czas dzialania algorytmu, od poczatku do celu, domyslnie wyswietlajaca wynik
	LARGE_INTEGER FB_list(int poczatek, int cel, bool wyp=true)
	{
		LARGE_INTEGER start, koniec, tm;
		Element *tmp;
		start = getTime(); //pobranie czasu
		int *poprzednik; //tablica poprzednikow
		poprzednik = new int[wierzcholki];
		int *obciazenie; //tablica obciazenia (drogi do wierzcholka)
		obciazenie = new int[wierzcholki];
		int obc = INT_MAX; //maksymalne obciazenie
		bool test; //zmiena sprawdzajaca czy mozna przerwac algorytm (nie ma zmian)
		for (int i = 0; i<wierzcholki; i++) //ustawienie danych domyslnych dla obciazenia i poprzednika
		{
			obciazenie[i] = INT_MAX;
			poprzednik[i] = -1;
		}
		obciazenie[poczatek] = 0;

		for (int i = 1; i < wierzcholki; i++) //wykonujemy liczba wierzcholkow -1 powtorzen
		{
			test = true; //zmienna sprawdzajaca czy nastepuje zmiana wartosci
			for (int j = 0; j < wierzcholki; j++) //sprawdzamy kazdy wierzcholek
			{
				tmp=tab[j].getPoczatek(); //pobieramy wskaznik na poczatek listy krawedzi wychodzacych z wierzcholka j
				while (tmp!=NULL) //dopoki elemnt istnieje
				{
					if (tmp->waga + obciazenie[j] < obciazenie[tmp->wierzcholek2] && obciazenie[j] != INT_MAX) //sprawdzamy czy jest krotsza droga z tego wierzcholka do nastepnego i czy mamy droge do tego wierzcholka
					{
						test = false; //zmieniamy  jakas wartosc, wiec moze pojawic sie nowe rozwiazanie
						obciazenie[tmp->wierzcholek2] = tmp->waga + obciazenie[j]; //zmieniamy dlugosc drogi
						poprzednik[tmp->wierzcholek2] = j; //ustawiamy wierzcholek z ktorego prowadzi najkrotsza droga
					}
					tmp = tmp->nastepny; //przechodzimy do kolejnej krawedzi
				}
			}
			if (test) break; //jesli nie ma zmian to przerywamy
		}

		koniec = getTime();
		if (wyp)
		{
			cout << "Forda-Bellmana-Listowo" << endl;
			if (cel == -1)
			{
				wypisz(obciazenie, poprzednik, wierzcholki);
			}
			else wypiszDrogeDoWierzcholka(obciazenie, poprzednik, wierzcholki, cel);
		}

		delete[]obciazenie;
		delete[]poprzednik;
		tm.QuadPart = koniec.QuadPart - start.QuadPart;
		return tm;
	}
private:

};

//Klasa reperezentujaca macierz incendencji
class MacierzIncendencji{
public:
	int wierzcholki; //liczba wierzcholkow
	int krawedzie; //liczba krawedzi
	int aktualnaKrawedz; //liczba dodanych krawedzi
	int **tab; //macierz incenencji
	//funkcja dodajaca zadana krawedz do macierzy (w zaleznosci od rodzaju grafu)
	void dodajKrawedz(int v1, int v2, int waga, bool skierowany){
		if (aktualnaKrawedz == krawedzie)//sprawedzenie czy trzeba tworzyc nowa macierz
		{
			//tworzenie nowej macierzy i przepisanie jej
			int **newTab;
			newTab = new int *[wierzcholki];
			for (int i = 0; i < wierzcholki; i++)
			{
				newTab[i] = new int[krawedzie + 1];
				for (int j = 0; j < krawedzie; j++)
				{
					newTab[i][j] = tab[i][j];
				}
				newTab[i][krawedzie] = 0;
			}
			krawedzie++;
			delete[] tab;
			tab = newTab;
		}
		tab[v1][aktualnaKrawedz] = waga; //dodanie wagi dla wierzcholka poczatkowego 
		if (!skierowany) tab[v2][aktualnaKrawedz] = waga; // dodanie wagi dla wierzcholka koncowego
		else tab[v2][aktualnaKrawedz] = -waga; //jesli graf skierowany do wierzcholek koncowy ma wage ujemna
		aktualnaKrawedz++; //zwiekszenie liczby dodanych krawedzi
	};

	//konstruktor tworzacy macierz incendencji o zadanej liczby wierzcholkow i krawedzi
	MacierzIncendencji(int w, int k){
		wierzcholki = w;
		krawedzie = k;
		aktualnaKrawedz = 0;
		tab = new int *[w];
		for (int i = 0; i < w; i++)
		{
			tab[i] = new int[k];
			for (int j = 0; j < k; j++)
			{
				tab[i][j] = 0;
			}
		}
	}
	//funkcja wyswietlajaca macierz
	void wyswietl()
	{
		for (int i = 0; i < wierzcholki; i++)
		{
			for (int j = 0; j < krawedzie; j++)
			{
				if (tab[i][j] < -9)  cout << tab[i][j] << " ";
				else if (tab[i][j]>9 || tab[i][j]<0) cout << " " << tab[i][j] << " ";
				else cout << "  " << tab[i][j] << " ";
			}
			cout << endl;
		}
	};

	//fukncja wykonujaca algorytm Kruskala dla reprezentacji macierzowej domyslnie wypisujaca wynik
	LARGE_INTEGER Kruskal_macierz(bool wyp = true)
	{
		LARGE_INTEGER start, koniec, tm;
		start = getTime(); //pobranie czasu
		Element *tmp;
		Lista tab2; //tablica wszystkich krawedzi
		Lista rozwiazanie; //tablica zawierajaca rozwiazanie
		int liczbaGrafow = wierzcholki; //liczba roznych grafow
		int *tabGrafow; //tabela grafow
		tabGrafow = new int[wierzcholki];

		for (int i = 0; i < wierzcholki; i++)
		{
			tabGrafow[i] = i; //ustawiamy kazdemu wierzcholkowi numer kolejnego grafu
		}

		//dodawanie krawedzi do tablicy wszystkich krawedzi i sortowanie ich wedlug wagi
		for (int j = 0; j < krawedzie; j++) //przeszukujemy kazda krawedz
		{
			int i;
			for (i = 0; i < wierzcholki; i++) //szukamy pierwszego wierzcholka
			{
				if (tab[i][j] >0) break;
			
			}
			for (int k = i+1; k < wierzcholki; k++)  //szukamy drugiego wierzcholka
			{
				if (tab[k][j] >0)
				{
					tmp = new Element(i, k, tab[i][j]);
					break;
				}
			}
			tab2.dodajWaga(*tmp); //dodajemy element sortujac go wedlug wagi
		}

		while (liczbaGrafow != 1) //dopoki liczba grafow jest rozna od 1
		{
			tmp = tab2.getPoczatek(); //pobieramy pierwszy element z posortowanej listy
			if (tabGrafow[tmp->wierzcholek1] != tabGrafow[tmp->wierzcholek2]) //sprawdzamy czy wierzcholki krawedzi naleza do tego samego grafu
			{
				rozwiazanie.dodaj(*tmp); //dodajemy rozwiazanie do listy rozwiazan
				int tmpW = tabGrafow[tmp->wierzcholek2]; //zapisujemy numer grafu drugiego wierzcholka
				for (int i = 0; i < wierzcholki; i++) //dla kazdego wierzcholka 
				{
					if (tabGrafow[i] == tmpW) tabGrafow[i] = tabGrafow[tmp->wierzcholek1]; //zmieniamy numer grafu drugiego wierzcholka na nuumer grafu pierwszego wierzcholka
				}
				liczbaGrafow--; //zmniejszamy liczbe grafow

			}
			tab2.usunPierwszy(); //usuwamy pierwszy element na liscie
		}
		koniec = getTime();
		if (wyp)
		{
			cout << "Kruskal-Macierzowo" << endl;
			rozwiazanie.wyswietlMST();
		}

		delete[]tabGrafow;
		tm.QuadPart = koniec.QuadPart - start.QuadPart;
		return tm;
	}

	//fukncja wykonujaca algorytm Prima dla reprezentacji macierzowej domyslnie wypisujaca wynik
	LARGE_INTEGER Prima_macierz(bool wyp = true)
	{
		LARGE_INTEGER start, koniec, tm;
		start = getTime(); //pobranie czasu
		Element *tmp;
		Lista tab2; //lista zawierajaca posortowana kolejke dostepnych krawedzi
		Lista rozwiazanie; //lista zawierajaca rozwiazanie
		bool *tabGrafow; //tabela czy wierzcholek nalezy do grafu
		tabGrafow = new bool[wierzcholki];
		for (int g = 0; g < wierzcholki; g++)
		{
			tabGrafow[g] = false; //ustawiamy domyslnie, ze wierzcholek nie nalezy
		}

		//wylosuj wierzcholek
		int poczatek = rand() % wierzcholki;
		tabGrafow[poczatek] = true; //dodajemy wierzcholek do grafu
		for (int j = 0; j < krawedzie; j++) //przeszukujemy kazda z krawedzi
		{
			if (tab[poczatek][j] >0)
			{
				//szukamy drugiego wierzcholka krawedzi (roznego od poczatku)
				for (int i = 0; i < poczatek; i++)
				{
					if (tab[i][j] >0) tmp = new Element(poczatek, i, tab[i][j]);
				}
				for (int i = poczatek+1; i < wierzcholki; i++)
				{
					if (tab[i][j] >0) tmp = new Element(poczatek, i, tab[i][j]);
				}
				tab2.dodajWaga(*tmp); //dodajemy element sortujac go wedlug wagi
			}
		}

		while (tab2.getSize() != 0) //dopoki lista krawedzi nie jest pusta
		{
			tmp = tab2.getPoczatek(); //pobieramy pierwszy elemnt z listy
			if (!tabGrafow[tmp->wierzcholek2]) //sprawdzamy czy wierzcholek docelowy nalezy do utworzonego juz grafu
			{
				tabGrafow[tmp->wierzcholek2] = true; //dodajemy wierzcholek do listy
				rozwiazanie.dodaj(*tmp);  //dodajemy rozwiazanie do listy rozwiazan
				poczatek = tmp->wierzcholek2; 

				tab2.usunPierwszy();
				for (int j = 0; j < krawedzie; j++)
				{
					if (tab[poczatek][j] >0)
					{
						for (int i = 0; i < poczatek; i++)
						{
							if (tab[i][j] >0) tmp = new Element(poczatek, i, tab[i][j]);
						}
						for (int i = poczatek+1; i < wierzcholki; i++)
						{
							if (tab[i][j] >0) tmp = new Element(poczatek, i, tab[i][j]);
						}
						tab2.dodajWaga(*tmp);
					}
				}
			}
			else
				tab2.usunPierwszy();

		}

		koniec = getTime();
		if (wyp)
		{
			cout << "Prim-Macierzowo" << endl;
			rozwiazanie.wyswietlMST();
		}

		delete[]tabGrafow;
		tm.QuadPart = koniec.QuadPart - start.QuadPart;
		return tm;
	}

	//fukncja wykonujaca algorytm Dijkstry dla reprezentacji macierzowej domyslnie wypisujaca wynik
	LARGE_INTEGER Dijkstry_macierz(int poczatek, int cel, bool wyp = true)
	{
		LARGE_INTEGER start, koniec, tm;
		start = getTime();
		Element *tmp =new Element();
		Lista tab2;
		bool *czy_sprawdzony;
		czy_sprawdzony = new bool[wierzcholki];
		int *poprzednik;
		poprzednik = new int[wierzcholki];
		int *obciazenie;
		obciazenie = new int[wierzcholki];
		int obc = INT_MAX;

		for (int g = 0; g < wierzcholki; g++)
		{
			czy_sprawdzony[g] = false;
			poprzednik[g] = -1;
			obciazenie[g] = INT_MAX;
		}
		obciazenie[poczatek] = 0;

		for (int i = 0; i < wierzcholki; i++)
		{
			for (int j = 0; j < krawedzie; j++)
			{
				if (tab[poczatek][j] >0)
				{
					for (int k = 0; k < krawedzie; k++)
					{
						if (tab[k][j] < 0)
						{
							 tmp = new Element(poczatek, k, tab[poczatek][j]);
							 break;
						}
					}
					tab2.dodajWaga(*tmp);
				}
			}
			while (tab2.getSize() != 0)
			{
				tmp = tab2.getPoczatek();
				if (obciazenie[tmp->wierzcholek2] > obciazenie[tmp->wierzcholek1] + tmp->waga)
				{
					obciazenie[tmp->wierzcholek2] = obciazenie[tmp->wierzcholek1] + tmp->waga;
					poprzednik[tmp->wierzcholek2] = tmp->wierzcholek1;
				}
				tab2.usunPierwszy();
			}
			czy_sprawdzony[poczatek] = true;
			obc = INT_MAX;
			for (int j = 0; j < wierzcholki; j++)
			{
				if (obc > obciazenie[j] && !czy_sprawdzony[j])
				{
					obc = obciazenie[j];
					poczatek = j;
				}
			}
		}


		koniec = getTime();
		if (wyp)
		{
			cout << "Dijkstry-Macierzowo" << endl;
			if (cel == -1)
			{
				wypisz(obciazenie, poprzednik, wierzcholki);
			}
			else wypiszDrogeDoWierzcholka(obciazenie, poprzednik, wierzcholki, cel);
		}


		delete[]obciazenie;
		delete[]czy_sprawdzony;
		delete[]poprzednik;
		tm.QuadPart = koniec.QuadPart - start.QuadPart;
		return tm;
	}

	//fukncja wykonujaca algorytm Bellmana Forda dla reprezentacji macierzowej domyslnie wypisujaca wynik
	LARGE_INTEGER FB_macierz(int poczatek, int cel, bool wyp = true)
	{
		LARGE_INTEGER start, koniec, tm;
		Element *tmp =new Element();

		int *poprzednik;
		poprzednik = new int[wierzcholki];
		int *obciazenie;
		obciazenie = new int[wierzcholki];
		int obc = INT_MAX;
		bool test;
		for (int i = 0; i<wierzcholki; i++)
		{
			obciazenie[i] = INT_MAX;
			poprzednik[i] = -1;
		}
		obciazenie[poczatek] = 0;
		start = getTime();
		for (int i = 1; i < wierzcholki; i++)
		{
			test = true;
			for (int j = 0; j < wierzcholki; j++)
			{
				for (int k = 0; k < krawedzie; k++)
				{
					if (tab[j][k] >0)
					{
						for (int l = 0; l < wierzcholki; l++)
						{
							if (tab[l][k] < 0)
							{
								tmp = new Element(j, l, tab[j][k]);
								break;
							}
						}
						if (tmp->waga + obciazenie[j] < obciazenie[tmp->wierzcholek2] && obciazenie[j] != INT_MAX)
						{
							test = false;
							obciazenie[tmp->wierzcholek2] = tmp->waga + obciazenie[j];
							poprzednik[tmp->wierzcholek2] = j;
						}
						tmp = tmp->nastepny;
					}

				}
			}
			if (test) break;
		}

		koniec = getTime();
		if (wyp){
			cout << "Forda-Bellmana-Listowo" << endl;
			if (cel == -1)
			{
				wypisz(obciazenie, poprzednik, wierzcholki);
			}
			else wypiszDrogeDoWierzcholka(obciazenie, poprzednik, wierzcholki, cel);
		}
		delete[]obciazenie;
		delete[]poprzednik;
		tm.QuadPart = koniec.QuadPart - start.QuadPart;
		return tm;
	}

private:

};


//funkcja generujaca liczbe krawedzi w zaleznosci od liczby wierzcholkow, gestosci grafu i tego czy jest on skierowany czy nie
int wygrenrujLiczbeKrawedzi(int wierzcholki, int gestosc, bool skierowany)
{
	int max_krawedzi = (wierzcholki*(wierzcholki - 1));//maksymalna liczba krawedzi
	int min_krawedzi = wierzcholki - 1; //minimalna liczba krawedzi
	int wym_krawedzi = (wierzcholki*max_krawedzi) / 100; //wymagana liczba krawedzi
	if (!skierowany) wym_krawedzi /= 2; //jesli nie jest skierowany to zmniejszamy liczbe krawedzi dwukrotnie
	if (wym_krawedzi < min_krawedzi) wym_krawedzi = min_krawedzi; //jesli liczba krawedzi mniejsza od wymaganej to wymagane krawedzie ustawiamy na minimalne
	return wym_krawedzi;
}

//funkcja tworzaca graf (skierwany lub nie) w macierzy incendencji i liscie sasiadow o zadanej liczbie wierzcholkow i krawedzi
void utworzGraf(MacierzIncendencji*& g1, ListaSasiadow*& g2, int wierzcholki, int wym_krawedzi, bool skierowany) {

	g1 = new MacierzIncendencji(wierzcholki, wym_krawedzi); //tworzymy macierz incendencji
	g2 = new ListaSasiadow(wierzcholki); //tworzymy liste sasiadow

	//Tworzymy drzewo rozpinajace
	int *tabp; //tablica numer wierzcholka
	//wierzcholki polaczone beda na jej konicu
	int tmp, poczatek, koniec, waga; //zmienne tymczasowe
	tabp = new int[wierzcholki];

	for (int i = 0; i < wierzcholki; i++) //kazdy wierzcholek jest osobnym grafem
	{
		tabp[i] = i;
	}

	//losujemy wierzcholek poczatkowy
	poczatek = rand() % wierzcholki;

	//i ustawiamy go na koncu tablicy grafow
	tabp[poczatek] = wierzcholki - 1;
	tabp[wierzcholki - 1] = poczatek;

	//tworzymy drzewo rozpinajace
	for (int i = 1; i < wierzcholki; i++)
	{
		//losujemy dwa wierzcholki, ktore chcemy polaczyc i ich wage
		poczatek = wierzcholki - i + rand() % i; //wierzcholek z naszego grafu
		koniec = rand() % (wierzcholki - i); //wierzcholek nie nalezacy do naszego grafu
		waga = rand() % 99 + 1; 

		//dodajemy krawedzie do listy i macierzy
		g1->dodajKrawedz(tabp[poczatek], tabp[koniec], waga, skierowany);
		g2->dodajKrawedz(tabp[poczatek], tabp[koniec], waga, skierowany);

	//przerzucamy nowo dodany wierzcholek na koniec tabeli
	tmp = tabp[koniec];
	tabp[koniec] = tabp[wierzcholki - i - 1];
	tabp[wierzcholki - i - 1] = tmp;
	}

	int k = wym_krawedzi - wierzcholki + 1; //ustalamy ile krawedzi musimy jeszcze utowrzyc
	
	//uzupelniamy drzewo kolejnymi krawedziami
	while (k-->0) //dopoki nie utworzymy wszystkich wymaganych krawedzi
	{
		//losujemy poczatek
		poczatek = rand() % wierzcholki;
		//jesli do wylosowanego wierzcholka nie mozna dodac juz krawedzi wtedy wybieramy kolejny
		while (g2->tab[poczatek].getSize() == wierzcholki - 1)
		{
			poczatek++;
			if (poczatek == wierzcholki) poczatek = 0;
		}
		//losujemy wierzcholek, z ktorym chcemy polaczyc wylosowany wczesniej poczatek
		koniec = rand() % wierzcholki;

		//musi byc rozny niz koniec
		if (koniec == poczatek){
			koniec++;
			if (koniec == wierzcholki) koniec = 0;
		}
		
		Element *tmp;
		tmp=g2->tab[poczatek].getPoczatek();
		//i musi nie byc juz polaczony wczesniej z tym samym wierzcholkiem

		while (tmp!= NULL) //dopoki element istnieje
		{
			if (tmp->wierzcholek2 > koniec) break; //jesli trafilismy na wierzcholek wyzszy niz ten ktory chcemy dodac oznacza, ze wierzcholki nie sa polaczone 
			else
			{
				if (tmp->wierzcholek2 == koniec) //jesli wierzcholek jest polaczony
				{
					koniec++; //bierzemy kolejny wierzcholek
					if (koniec == poczatek){ //sprawdzamy czy nowy wierzcholek nie jest poczatkiem
						koniec++; 
					}
					if (koniec == wierzcholki) // i  czy nie jest rowny liczbie wierzcholkow
					{
						if (poczatek!=0) koniec = 0; //jesli poczatkowym wierzcholkiem nie jest 0 zmieniamy nowy wierzcholek na 0 
						else koniec = 1; //jesli jest to na 1
						tmp = g2->tab[poczatek].getPoczatek(); //szukamy wierzcholka od poczatku
					}
				}
				else
					tmp = tmp->nastepny; //przechodzimy do nastepnej krawedzi na liscie
			}
		}	
		
		//losujemy wage
		waga = rand() % 99 + 1;

		//dodajemy krawedzie
		g1->dodajKrawedz(poczatek, koniec, waga, skierowany);
		g2->dodajKrawedz(poczatek, koniec, waga, skierowany);

	}
	cout << "Wygenerowany-Grafy" << endl;
}

//funkcja wczytujaca graf (skierowany lub nie) z pliku do macierzy incendencji i listy sasiadow
void wczytajGraf(MacierzIncendencji*& g1, ListaSasiadow*& g2, bool skierowany)
{
	string nazwa;
	cout << "\nPodaj nazwe pliku, z ktorego chcesz wczytac graf (wraz z rozszerzeniem): ";
	cin >> nazwa;

	ifstream plik;
	plik.open(nazwa);

	int krawedzie; //wczytanie liczby krawedzi
	int wierzcholki; //wczytanie liczy wierzcholkow
	plik >> krawedzie >> wierzcholki;

	g1 = new MacierzIncendencji(wierzcholki, krawedzie);
	g2 = new ListaSasiadow(wierzcholki);

	//wczytywanie kolejnych krawedzi
	while (krawedzie-->0) {
		int v1, v2, w;
		plik >> v1 >> v2 >> w;
		g1->dodajKrawedz(v1, v2, w, skierowany);
		g2->dodajKrawedz(v1, v2, w, skierowany);
	}

	plik.close();

}
void test()
{
	MacierzIncendencji *macierz = nullptr;
	ListaSasiadow *lista = nullptr;

	int poczatek = 0;
	int koniec = 1;
	int krawedzie = 0;

	//tablice przechowujace wynik
	_LARGE_INTEGER LP[5][4];
	_LARGE_INTEGER LK[5][4];
	_LARGE_INTEGER LD[5][4];
	_LARGE_INTEGER LB[5][4];
	_LARGE_INTEGER MP[5][4];
	_LARGE_INTEGER MK[5][4];
	_LARGE_INTEGER MD[5][4];
	_LARGE_INTEGER MB[5][4];

	int w[5] = { 50, 100, 150, 200, 250 }; //tablica wierzcholkow
	int k[4] = { 25, 50, 75, 99 }; //tablica gestosci

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << i << " " << j << endl;
			krawedzie = wygrenrujLiczbeKrawedzi(w[i], krawedzie, false); 
			utworzGraf(macierz, lista, w[i], k[j], false);
			LP[i][j].QuadPart = 0;
			MP[i][j].QuadPart = 0;
			LK[i][j].QuadPart = 0;
			MK[i][j].QuadPart = 0;
			cout << "Algorytm MST ";
			for (int d = 0; d < 10; d++)
			{
				cout << ".";
				LP[i][j].QuadPart += lista->Prima_list(false).QuadPart;
				MP[i][j].QuadPart += macierz->Prima_macierz(false).QuadPart;
				LK[i][j].QuadPart += lista->Kruskal_list(false).QuadPart;
				MK[i][j].QuadPart += macierz->Kruskal_macierz(false).QuadPart;
			}
			cout << endl;
			LP[i][j].QuadPart /= 10;
			MP[i][j].QuadPart /= 10;
			LK[i][j].QuadPart /= 10;
			MK[i][j].QuadPart /= 10;

			krawedzie = wygrenrujLiczbeKrawedzi(w[i], krawedzie, true);
			utworzGraf(macierz, lista, w[i], k[j], true);

			LB[i][j].QuadPart = 0;
			MB[i][j].QuadPart = 0;
			LD[i][j].QuadPart = 0;
			MD[i][j].QuadPart = 0;
			cout << "Algorytm PS ";
			for (int d = 0; d < 10; d++)
			{
				cout << ".";
				LB[i][j].QuadPart += lista->FB_list(poczatek, koniec, false).QuadPart;
				MB[i][j].QuadPart += macierz->FB_macierz(poczatek, koniec, false).QuadPart;
				LD[i][j].QuadPart += lista->Dijkstry_list(poczatek, koniec, false).QuadPart;
				MD[i][j].QuadPart += macierz->Dijkstry_macierz(poczatek, koniec, false).QuadPart;
			}
			cout << endl;
			LB[i][j].QuadPart /= 10;
			MB[i][j].QuadPart /= 10;;
			LD[i][j].QuadPart /= 10;;
			MD[i][j].QuadPart /= 10;
		}
	}
	std::fstream liniowo;
	std::fstream macierzowo;
	std::fstream gestosc1;
	std::fstream gestosc2;
	std::fstream gestosc3;
	std::fstream gestosc4;
	gestosc1.open("gestosc1.txt", std::ios::out);
	gestosc2.open("gestosc2.txt", std::ios::out);
	gestosc3.open("gestosc3.txt", std::ios::out);
	gestosc4.open("gestosc4.txt", std::ios::out);

	liniowo.open("liniowo.txt", std::ios::out);
	macierzowo.open("macierzowo.txt", std::ios::out);

	gestosc1 << k[0] << ";PL;PM;KL;KM;DL;DM;BL;BM" << endl;
	gestosc2 << k[1] << ";PL;PM;KL;KM;DL;DM;BL;BM" << endl;
	gestosc3 << k[2] << ";PL;PM;KL;KM;DL;DM;BL;BM" << endl;
	gestosc4 << k[3] << ";PL;PM;KL;KM;DL;DM;BL;BM" << endl;
	liniowo << "wierzcholki;gestosc;PL;KL;DL;BL" << endl;
	macierzowo << "wierzcholki;gestosc;PM;KM;DM;BM" << endl;
	for (int j = 0; j < 5; j++)
	{
		gestosc1 << w[j] << ";" << LP[0][j].QuadPart << ";" << MP[0][j].QuadPart << ";" << LK[0][j].QuadPart << ";" << MK[0][j].QuadPart << ";";
		gestosc1 << LD[0][j].QuadPart << ";" << MD[0][j].QuadPart << ";" << LB[0][j].QuadPart << ";" << MB[0][j].QuadPart << endl;
		gestosc2 << w[j] << ";" << LP[1][j].QuadPart << ";" << MP[1][j].QuadPart << ";" << LK[1][j].QuadPart << ";" << MK[1][j].QuadPart << ";";
		gestosc2 << LD[1][j].QuadPart << ";" << MD[1][j].QuadPart << ";" << LB[1][j].QuadPart << ";" << MB[1][j].QuadPart << endl;
		gestosc3 << w[j] << ";" << LP[2][j].QuadPart << ";" << MP[2][j].QuadPart << ";" << LK[2][j].QuadPart << ";" << MK[2][j].QuadPart << ";";
		gestosc3 << LD[2][j].QuadPart << ";" << MD[2][j].QuadPart << ";" << LB[2][j].QuadPart << ";" << MB[2][j].QuadPart << endl;
		gestosc4 << w[j] << ";" << LP[3][j].QuadPart << ";" << MP[3][j].QuadPart << ";" << LK[3][j].QuadPart << ";" << MK[3][j].QuadPart << ";";
		gestosc4 << LD[3][j].QuadPart << ";" << MD[3][j].QuadPart << ";" << LB[3][j].QuadPart << ";" << MB[3][j].QuadPart << endl;

		for (int i = 0; i < 4; i++)
		{
			liniowo << w[j] << ";" << k[i] << ";" << LP[i][j].QuadPart << ";" << LK[i][j].QuadPart << ";" << LD[i][j].QuadPart << ";" << LB[i][j].QuadPart << endl;
			macierzowo << w[j] << ";" << k[i] << ";" << MP[i][j].QuadPart << ";" << MK[i][j].QuadPart << ";" << MD[i][j].QuadPart << ";" << MB[i][j].QuadPart << endl;
		}
	}
	gestosc1.close();
	gestosc2.close();
	gestosc3.close();
	gestosc4.close();

	liniowo.close();
	macierzowo.close();

}


int main() {
	ListaSasiadow* lista = nullptr; //reprezentacja listy
	MacierzIncendencji* macierz = nullptr; //reprezentacja macierzy

	KOLOR_NORMALNY; //kolor ekranu
	int wierzcholki, krawedzie, poczatek, koniec;  //liczba wierzcholkow

	char opcja;
	bool petla = true; //petla glownego programu
	bool petla2 = false; //petla bocznego programu
	bool skierowany;
	while (petla)
	{
		system("cls");
		cout << "To jest program badajacy efektywnosc algorytmow grafowych\n";
		cout << "************************************\n";
		cout << "Wybierz, ktore algorytmy chcesz testowac(1-3):\n";
		cout << "1. Algorytm MST\n";
		cout << "2. Algorytm najkrotszej drogi\n";
		cout << "3. Zakoncz\n";
		cout << "************************************\n";
		opcja = _getch();
		switch (opcja) {
		case '1':
			skierowany = false;
			petla2 = true;
			while (petla2)
			{
				system("cls");
				cout << "To jest czesc programu odpowiedzialna za znajdowanie mnimalnego drzewa rozpinajacego\n";
				cout << "************************************\n";
				cout << "Wybierz co chcesz zrobic(1-6):\n";
				cout << "1. Wczytaj z pliku\n";
				cout << "2. Wygrenruj graf losowo\n";
				cout << "3. Wyswietl listowo i macierzowo na ekranie\n";
				cout << "4. Algorytm Kruskala\n";
				cout << "5. Algorytm Prima\n";
				cout << "6. Zamknij\n";
				cout << "************************************\n";
				opcja = _getch();
				switch (opcja) {
				case '1':
					wczytajGraf(macierz, lista, skierowany);
					cout << "\nGraf zostal wczytany do pamieci komputera.\n";
					break;
				case '2':
					fflush(stdin);
					cout << "\nPodaj liczbe wierzcholkow: ";
					cin >> wierzcholki;
					cout << "\nPodaj gestosc (0-100): ";
					cin >> krawedzie;
					krawedzie = wygrenrujLiczbeKrawedzi(wierzcholki, krawedzie, skierowany);
					utworzGraf(macierz, lista, wierzcholki, krawedzie, skierowany);
					break;
				case '3':
					lista->wyswietl();
					macierz->wyswietl();
					break;
				case '4':
					lista->Kruskal_list();
					macierz->Kruskal_macierz();
					break;
				case '5':
					lista->Prima_list();
					macierz->Prima_macierz();
					break;
				case '6': petla2 = false; break;
				}
				nacisnij();
			}
			break;
		case '2':
			petla2 = true;
			skierowany = true;
			while (petla2)
			{
				system("cls");
				cout << "To jest czesc programu odpowiedzialna za znajdowanie najkrotszej drogi\n";
				cout << "************************************\n";
				cout << "Wybierz co chcesz zrobic(1-6):\n";
				cout << "1. Wczytaj z pliku\n";
				cout << "2. Wygrenruj graf losowo\n";
				cout << "3. Wyswietl listowo i macierzowo na ekranie\n";
				cout << "4. Algorytm Dijkstry\n";
				cout << "5. Algorytm Forda-Bellmana\n";
				cout << "6. Zamknij\n";
				cout << "************************************\n";
				opcja = _getch();
				switch (opcja) {
				case '1':
					wczytajGraf(macierz, lista, skierowany);
					cout << "\nGraf zostal wczytany do pamieci komputera.\n";
					break;
				case '2':
					fflush(stdin);
					cout << "\nPodaj liczbe wierzcholkow: ";
					cin >> wierzcholki;
					cout << "\nPodaj gestosc (0-100): ";
					cin >> krawedzie;
					krawedzie = wygrenrujLiczbeKrawedzi(wierzcholki, krawedzie, skierowany);
					utworzGraf(macierz, lista, wierzcholki, krawedzie, skierowany);
					break;
				case '3':
					lista->wyswietl();
					macierz->wyswietl();
					break;
				case '4':
					fflush(stdin);
					cout << "\nPodaj poczatkowy wierzcholek: ";
					cin >> poczatek;
					cout << "\nPodaj koncowy wierzcholek (-1 wyswietli  wszystkie): ";
					cin >> koniec;
					lista->Dijkstry_list(poczatek,koniec);
					macierz->Dijkstry_macierz(poczatek,koniec);
					break;
				case '5':
					fflush(stdin);
					cout << "\nPodaj poczatkowy wierzcholek: ";
					cin >> poczatek;
					cout << "\nPodaj koncowy wierzcholek (-1 wyswietli  wszystkie): ";
					cin >> koniec;
					lista->FB_list(poczatek, koniec);
					macierz->FB_macierz(poczatek, koniec);
					break;
				case '6': petla2 = false; break;
				}
				nacisnij();
			}
			break;
		case '3': petla = false; break; //zakonczenie dzialania programu

		case '4': 			//test
			test();
			nacisnij();
			break;
		}
	}

	system("pause");
	return 0;
}


