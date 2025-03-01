#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <Windows.h>

using namespace std;


void wellcome();
void loadingbar();
void loadingbar_cake(int);
void meniu();


class reteta
{
	string _nume_reteta;
	int _timp_preparare;

public:
	reteta(string nume, int timp)
	{
		this->_nume_reteta = nume;
		this->_timp_preparare = timp;
	}

	void afisare_r()
	{
		cout << endl << "\t\t\t";
		cout << " -> Denumire: " << this->_nume_reteta << ", timp: " << this->_timp_preparare << endl;
		Sleep(200);
	}

	string Nume_r()
	{
		return this->_nume_reteta;
	}

	int Timp_r()
	{
		return this->_timp_preparare;
	}
};

class prajitura
{
	string _nume;
	reteta* Reteta;

public:
	prajitura(string nume, reteta* R)
	{
		this->_nume = nume;
		this->Reteta = R;
	}

	virtual void afisare()
	{
		cout << "Nume: " << this->_nume << endl;
		cout << "Reteta: " << endl;
		Reteta->afisare_r();
		cout << "-------------------------------" << endl << endl;
	}

	void afisare_nume_prajitura()
	{
		cout << endl << "\t\t\t\t";
		cout << "-> " << this->_nume << endl;
		Sleep(200);
	}

	string getNume()
	{
		return this->_nume;
	}

	string getNume_R()
	{
		return this->Reteta->Nume_r();
	}

	int getTimp()
	{
		return this->Reteta->Timp_r();
	}
};

class prajitura_obisnuita :public prajitura
{
public:
	prajitura_obisnuita(string nume, reteta* R) :prajitura(nume, R)
	{
	}
};

class prajitura_diabetici : public prajitura
{
	float _cantitate_zahar;

public:
	prajitura_diabetici(string nume, reteta* R, float zahar) :prajitura(nume, R)
	{
		this->_cantitate_zahar = zahar;
	}

	void afisare() override
	{
		cout << "Nume: " << getNume() << endl;
		cout << "Reteta: " << endl;
		cout << "Denumire: " << getNume_R() << ", timp: " << getTimp() << " minute" << endl;
		cout << "Cantitate zahar: " << this->_cantitate_zahar << endl;
		cout << "-------------------------------" << endl << endl;
	}
};

class depozit
{
private:
	int capacitate_max = 10;
	list<prajitura*> lista_depozit;

public:

	depozit(list<prajitura*> p)
	{
		this->lista_depozit = p;
	}

	void add(prajitura* p)
	{
		lista_depozit.push_back(p);
	}

	void afisare_depozit()
	{
		for (auto d : lista_depozit)
			d->afisare_nume_prajitura();
	}

	int get_capacitate_max()
	{
		return 	this->capacitate_max;
	}

	friend class PanouControl;
};


class preparator
{
private:
	list <reteta*> retete_cunoscute;

public:
	preparator(list<reteta*> p)
	{
		this->retete_cunoscute = p;
	}

	prajitura* Comanda(string nume, reteta* R)
	{
		int timp_asteptare = R->Timp_r();

		//Sleep(1000 * timp_asteptare);
		loadingbar_cake(timp_asteptare);

		prajitura* p = new prajitura(nume, R);

		cout << endl << endl << "\t\t\t\t";
		cout << "-> S-a creat prajitura!";
		Sleep(200);
		cout << endl << endl << "\t\t\t";
		cout << "       -> Prajitura este servita!";
		Sleep(200);

		return p;
	}

	void afisare_retete()
	{
		for (auto r : retete_cunoscute)
			r->afisare_r();
	}

	void afisare_retete_numar()
	{
		int n = 1;
		for (auto r : retete_cunoscute)
		{
			cout << endl << "\t\t\t";
			cout << n << ". ";
			cout << "Denumire: " << r->Nume_r() << ", timp: " << r->Timp_r() << endl;
			Sleep(200);
			n++;
		}
	}


	friend class PanouControl;
};

class PanouControl
{
	preparator* _p;
	depozit* _d;

public:
	//constructor 
	PanouControl(depozit* d, preparator* p)
	{
		this->_d = d;
		this->_p = p;
	}

	void afisare_nume_prajituri_depozit()
	{
		_d->afisare_depozit();
		cout << endl;
	}

	void afisare_prajituri_posibile()
	{
		_p->afisare_retete();
		cout << endl;
	}

	prajitura* Primire_Comanda(string nume_prajitura)
	{
		list <prajitura*> ::iterator it;
		it = _d->lista_depozit.begin();
		int ok = 0;
		int nr, poz;
		for (auto a : _d->lista_depozit)
			if (a->getNume() == nume_prajitura)
			{
				ok = 1;
				_d->lista_depozit.erase(it);

				cout << endl << endl << "\t\t\t";
				cout << "~ Prajitura este servita!" << endl;
				return a;
			}
			else
				advance(it, 1);

		if (ok == 0)
		{
			int ok_r = 0;
			cout << endl << endl;
			cout << "~ Prajitura dorita nu se afla in depozit, dar o putem crea folosind o reteta de mai jos: " << endl;
			Sleep(200);
			_p->afisare_retete_numar();
			cout << endl << "\t\t";
			cout << "~ Va rugam alegeti o reteta, introducand numarul acesteia:" << endl;
			Sleep(200);

			poz = 1;

			do {

				cout << endl << "\t\t\t\t";
				cin >> nr;
				if (nr<1 || nr>_p->retete_cunoscute.size())
				{
					cout << endl << "\t\t";
					cout << "~ Ati introdus o reteta gresita!";
					Sleep(200);
					cout << endl << endl << "\t\t";
					cout << "~ Mai incercati, introducand numarul retetei dorite!  ";
					Sleep(200);

				}


			} while (nr<1 || nr>_p->retete_cunoscute.size());


			for (auto r : _p->retete_cunoscute)
				if (poz < nr)
					poz++;
				else
				{
					cout << endl << endl << "\t\t\t";
					cout << "~ Ati ales reteta cu numarul " << poz;
					cout << endl << endl << "\t\t\t";
					Sleep(200);
					cout << "~ Va rugam asteptati..." << endl;
					Sleep(1000);
					return _p->Comanda(nume_prajitura, r);
				}


		}
	}

	void umplere_depozit(prajitura* p)
	{
		if (_d->lista_depozit.size() == 0)
			for (int i = 1; i <= _d->capacitate_max; i++)
				_d->add(p);
	}
};

//initializare depozit si lista de retete stiute din fiser
void initializare_din_fisier(list<prajitura*>& depozit_l, list<reteta*>& lista_prajituri_posibile)
{
	depozit* d = new depozit(list<prajitura*>());
	ifstream f;
	int capacitate = 1;


	f.open("retete.txt", ios::in);
	string nume, nume_r;
	int timp, tip;
	float zahar;

	while (f >> nume && capacitate <= d->get_capacitate_max())
	{
		f >> nume_r;
		f >> timp;
		f >> tip;
		reteta* r = new reteta(nume_r, timp);
		lista_prajituri_posibile.push_back(r);
		if (tip == 1)
		{
			prajitura_obisnuita* p1 = new prajitura_obisnuita(nume, r);
			prajitura* P = p1;
			depozit_l.push_back(P);
		}
		else
			if (tip == 2)
			{
				f >> zahar;
				prajitura_diabetici* p2 = new prajitura_diabetici(nume, r, zahar);
				prajitura* P = p2;
				depozit_l.push_back(P);
			}
		capacitate++;
	}
	f.close();
}

/*
//supraincarcare operator
istream& operator >> (istream & flux_in, list<prajitura*> &list_depozit, list<reteta*> &prajituri_posibile)
{
 initializare_din_fisier(list_depozit, prajituri_posibile);
	return flux_in;
}
*/

int main()
{
	list<prajitura*> depozit_lista;
	list<reteta*> prajituri_posibile;

	int opt;
	fstream f;

	system("title Cake Maker");
	system("mode con: cols=90");

	loadingbar();
	system("cls");
	wellcome();
	system("cls");


	//citeste lista de prajituri din depozit din fisier
	initializare_din_fisier(depozit_lista, prajituri_posibile);

	//declar un obiect de tipul Panou
	PanouControl* P = new PanouControl(new depozit(depozit_lista), new preparator(prajituri_posibile));

	string nume_prajitura_comandata;

	do {

		meniu();

		cout << endl << "\t\t\t\t";
		cin >> opt;
		switch (opt)
		{
		case 1:
		{
			system("cls");
			cout << endl << endl << "\t";
			cout << " ~ Acest aparat poate crea prajituri utilizand urmatoarele retete: " << endl;
			Sleep(200);

			P->afisare_prajituri_posibile();

			cout << endl << endl << "\t\t\t";
			system("pause");
			break;

		}

		case 2:
		{
			system("cls");
			cout << endl << endl << "\t";
			cout << "~In momentul actual, acest aparat dispune de urmatoarele prajituri:" << endl;
			Sleep(200);

			P->afisare_nume_prajituri_depozit();

			cout << endl << endl << "\t\t\t";
			system("pause");
			break;
		}

		case 3:
		{
			system("cls");
			cout << endl << endl << "\t";
			Sleep(200);
			cout << "~ Pentru plasarea unei comenzi va rugam introduceti numele prajiturii dorite: ";
			try
			{
				cout << endl << endl << "\t\t\t\t -> ";
				cin >> nume_prajitura_comandata;
				Sleep(200);

				if (nume_prajitura_comandata.size() > 10)
					throw new exception("~ Numele prajiturii nu poate depasi 10 caractere, mai incercati!");

			}

			catch (exception* e)
			{
				cout << endl << endl << "\t";
				cout << e->what() << endl << endl;
				Sleep(200);
				cout << endl << endl << "\t\t\t";
				system("pause");
				f.open("log.txt", ios::app);
				f << e->what() << endl;
				f.close();
				break;
			}

			//prajitura *prajitura_umplere;
			//prajitura_umplere = P->Primire_Comanda(nume_prajitura_comandata);
			//cout << endl << endl << "\t\t\t";
			//cout << prajitura_umplere->getNume() << endl;
			//P->umplere_depozit(prajitura_umplere);

			P->umplere_depozit(P->Primire_Comanda(nume_prajitura_comandata));

			cout << endl << endl << endl << endl << "\t\t\t";
			system("pause");
			break;
		}

		case 0:
		{
			system("cls");
			Sleep(300);
			cout << endl << endl << endl << endl << endl << "\t\t\t";
			cout << ">> Multumim ca ati cumparat de la noi!";
			Sleep(300);

			cout << endl << endl << "\t\t\t";
			cout << "  >> Va mai asteptam cu drag! :)";
			Sleep(300);

			cout << endl << endl << "\t\t\t\t";
			cout << ">> O zi buna!";
			Sleep(400);
			cout << endl << endl << endl;

			exit(1);
		}


		default:
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << "\t\t\t";
			cout << "~ Optiune gresita, mai incercati..." << endl;
			Sleep(200);
			cout << endl << endl << endl << "\t\t\t";
			system("pause");
			break;
		}

		}


	} while (opt);

	return 0;
}


void loadingbar()
{
	for (int i = 15; i <= 100; i += 5)
	{

		system("cls");
		cout << endl << endl << endl << endl << endl << endl << endl << "\t\t\t\t";
		cout << i << " % Loading..." << endl << endl << "\t\t";

		for (int j = 0; j < i; j += 2)
		{
			cout << " ";
		}

		Sleep(200);
	}
}

void loadingbar_cake(int timp)
{

	for (int i = 15; i <= 100; i += 5)
	{
		system("cls");
		cout << endl << endl << endl << endl << endl << endl << endl << "\t\t\t\t";
		cout << i << " % Loading..." << endl << endl << "\t\t";


		for (int j = 0; j < i; j += 2)
		{
			cout << " ";
		}

		Sleep(timp * 1000 / 18);
	}
}

void wellcome()
{
	int i;
	string welcome = "BUN VENIT";
	string welcome2 = " LA";
	string welcome3 = " ''HAPPY CAKE MAKER'' ";
	cout << endl << endl << endl << endl << endl << "\t\t\t";
	for (i = 0; i < welcome.size(); i++)
	{

		cout << welcome[i];
		Sleep(100);
	}

	cout << endl << endl << "\t\t\t\t ";
	for (i = 0; i < welcome2.size(); i++)
	{

		cout << welcome2[i];
		Sleep(100);
	}

	cout << endl << endl << endl << "\t\t\t ";
	for (i = 0; i < welcome3.size(); i++)
	{

		cout << welcome3[i];
		Sleep(100);
	}
	Sleep(500);

}

void meniu()
{
	system("cls");

	cout << endl << endl << endl << endl << endl << "\t\t\t";
	cout << ">> 1. Prajituri posibile";
	Sleep(400);

	cout << endl << endl << "\t\t\t";
	cout << ">> 2. Prajituri existente";
	Sleep(400);

	cout << endl << endl << "\t\t\t";
	cout << ">> 3. Comanda prajitura";
	Sleep(400);

	cout << endl << endl << "\t\t\t";
	cout << ">> 0. Iesire";
	Sleep(400);

	cout << endl << endl << "\t\t\t";
	cout << "Alegeti optiunea dorita: ";
	Sleep(400);
}