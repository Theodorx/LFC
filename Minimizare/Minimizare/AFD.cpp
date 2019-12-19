#include "AFD.h"
#include <fstream>
#include<tuple>
#include<iostream>
#include<string>
AFD AFD::CitireDinFisier(const std::string& Fisier)
{
	int Contor1, Contor2, Contor3, Contor4;
	std::string Aux, Aux1, Aux2;
	std::ifstream Fis(Fisier);
	std::vector<std::string> stari;
	std::vector<std::string> sigma;
	std::vector<std::tuple<std::string, std::string, std::string>> delta;
	std::string stareInit;
	std::vector<std::string> stariFinale;
	while (!Fis.eof())
	{   //Citim Stari

		Fis >> Contor1 >> Contor2 >> Contor3 >> Contor4;
		for (int i = 0; i < Contor1; i++)
		{
			Fis >> Aux;
			stari.emplace_back(Aux);
		}
		//Citim Sigma
		for (int i = 0; i < Contor2; i++)
		{
			Fis >> Aux;
			sigma.emplace_back(Aux);
		}
		//Citim Delta
		for (int i = 0; i < Contor3; i++)
		{
			Fis >> Aux >> Aux1 >> Aux2;
			delta.emplace_back(std::make_tuple(Aux, Aux1, Aux2));

		}
		//Citim StareInit
		Fis >> stareInit;
		//Cotim starile finale
		for (int i = 0; i < Contor4; i++)
		{
			Fis >> Aux;
			stariFinale.emplace_back(Aux);
		}
	}
	return AFD(stari, sigma, delta, stareInit, stariFinale);

}

void AFD::ScrieInFisier(const std::string& Fisier)
{
	std::ofstream myFile;
	myFile.open(Fisier);
	myFile.clear();
	myFile << "Stari: ";
	for (int i = 0; i < m_stari.size(); i++)
		myFile << m_stari[i] << " ";
	myFile << std::endl;

	myFile << "Sigma: ";
	for (int i = 0; i < m_sigma.size(); i++)
		myFile << m_sigma[i] << " ";
	myFile << std::endl;

	myFile << "Delta: ";
	for (int i = 0; i < m_delta.size(); i++)
		myFile << "\n" << std::get<0>(m_delta[i]) << " " << std::get<1>(m_delta[i]) << " " << std::get<2>(m_delta[i]);
	myFile << std::endl;

	myFile << "Stare Initiala: " << m_stareInit << "\n";
	myFile << "Stari Finale: ";
	for (int i = 0; i < m_stariFinale.size(); i++)
		myFile << m_stariFinale[i] << " ";
	myFile << std::endl;
	myFile.close();
}



void AFD::Afisare()
{
	std::cout << "Stari: ";
	for (int i = 0; i < m_stari.size(); i++)
		std::cout << m_stari[i] << " ";
	std::cout << std::endl;

	std::cout << "Sigma: ";
	for (int i = 0; i < m_sigma.size(); i++)
		std::cout << m_sigma[i] << " ";
	std::cout << std::endl;

	std::cout << "Delta: ";
	for (int i = 0; i < m_delta.size(); i++)
		std::cout << "\n" << std::get<0>(m_delta[i]) << " " << std::get<1>(m_delta[i]) << " " << std::get<2>(m_delta[i]);
	std::cout << std::endl;

	std::cout << "Stare Initiala: " << m_stareInit << "\n";
	std::cout << "Stari Finale: ";
	for (int i = 0; i < m_stariFinale.size(); i++)
		std::cout << m_stariFinale[i] << " ";
	std::cout << std::endl;
}

std::string AFD::VerificareCuvant(std::string Cuvant)
{

	std::string stareCurenta = m_stareInit;
	for (int i = 0; i < Cuvant.size(); i++)
	{
		bool State = false;
		for (int j = 0; j < m_delta.size(); j++)
		{
			if (stareCurenta == std::get<0>(m_delta[j]) && Cuvant[i] == std::get<1>(m_delta[j])[0])
			{
				stareCurenta = std::get<2>(m_delta[j]);
				State = true;
				break;
			}
		}
		if (State == false)
		{
			return"Blocaj\n";
		}
	}
	for (int i = 0; i < m_stariFinale.size(); i++)
		if (stareCurenta == m_stariFinale[i])
			return "Cuvant Acceptat\n";
	return "Cuvant Neacceptat\n";
}

void AFD::Minimizare()
{  //Starea e finala sau nefinala;
	std::vector<std::vector<int>> tabel;
	std::vector<bool> finalSauNefinal;
	bool finsauNefin;
	for (int i = 0; i < m_stari.size(); i++)
	{
		finsauNefin = false;
		for (int j = 0; j < m_stariFinale.size(); j++)
			if (m_stari[i] == m_stariFinale[j])
				finsauNefin = true;
		if (finsauNefin == true)
			finalSauNefinal.emplace_back(true);
		else
			finalSauNefinal.emplace_back(false);
	}
	//Am creeat tabelul
	for (int i = 0; i < m_stari.size(); i++)
	{
		tabel.emplace_back(i);
		for (int j = 0; j < i + 1; j++);
		if (tabel.size() - 1 == i)
			tabel[i].emplace_back(i);
		else
			tabel[i].emplace_back(0);
	}
	//Completam prima etapa a tabelului
	for (int i = 0; i < tabel.size(); i++)
		for (int j = 0; j < tabel[i].size() - 1; j++)
		{
			if ((finalSauNefinal[j] == true && finalSauNefinal[i] == false) || (finalSauNefinal[j] == false && finalSauNefinal[i] == true))
			{
				tabel[i][j] = -2;
			}
		}
	bool incaOParcugere = true;
	std::vector<bool> ExistaCale;
	for (int i = 0; i < m_sigma.size(); i++)
		ExistaCale.emplace_back(false);

	while (incaOParcugere == true)
	{
		incaOParcugere = false;

		for (int i = 0; i < tabel.size(); i++)
			for (int j = 0; j < tabel[i].size() - 1; j++)
			{
				std::string oStare = "";
				std::string altaStare = "";
				bool boolOStare = false;
				bool boolAltaStare = false;
				if (tabel[i][j] == 0)
				{
					for (int w = 0; w < m_sigma.size(); w++)
					{
						oStare = "";
						altaStare = "";
						boolOStare = false;
						boolAltaStare = false;
						for (int z = 0; z < m_delta.size(); z++)
						{
							if (std::get<0>(m_delta[z]) == m_stari[j] && std::get<1>(m_delta[z]) == m_sigma[w])
							{
								oStare = std::get<2>(m_delta[z]);
								boolOStare = true;
							}
							if (std::get<0>(m_delta[z]) == m_stari[i] && std::get<1>(m_delta[z]) == m_sigma[w])
							{
								altaStare = std::get<2>(m_delta[z]);
								boolAltaStare = true;
							}

						}
						if ((oStare != altaStare) && (boolOStare == true) && (boolAltaStare == true))
						{

							int coord1;
							int coord2;
							for (int k = 0; k < m_stari.size(); k++)
							{
								if (oStare == m_stari[k])
									coord1 = k;
								if (altaStare == m_stari[k])
									coord2 = k;
							}
							if (coord1 < coord2)
								std::swap(coord1, coord2);
							if (tabel[coord1][coord2] == -2)
							{
								tabel[i][j] = -2;
								incaOParcugere = true;
							}
						}
					}

				}
				
			}		
	}
	std::vector<std::pair<int,int>> stariNemarcate;
	for(int i=0;i<tabel.size();i++)
		for (int j = 0; j < tabel[i].size()-1; j++)
		{
			if (tabel[i][j] == 0)
				stariNemarcate.emplace_back(std::make_pair(j, i));
		}
	for (int i = 0; i < stariNemarcate.size(); i++)
		std::cout << "\nPerechile nemarcate sunt: " << m_stari[stariNemarcate[i].first]<<" "<<m_stari[stariNemarcate[i].second]<<std::endl;

	std::system("pause");
	for (int i = 0; i < stariNemarcate.size(); i++)
	{   //m_delta
		for (int j = 0; j < m_delta.size(); j++)
		{   
			if ((std::get<0>(m_delta[j]) == m_stari[stariNemarcate[i].first]) || (std::get<0>(m_delta[j]) == m_stari[stariNemarcate[i].second]))
			{
				std::get<0>(m_delta[j])[0] = 'P';
			}
			if ((std::get<2>(m_delta[j]) == m_stari[stariNemarcate[i].first]) || (std::get<2>(m_delta[j]) == m_stari[stariNemarcate[i].second]))
			{
				std::get<2>(m_delta[j])[0] = 'P';
			}

		}
		//o singura stare
		std::string ramaneOStare;
		for (int j = 0; j < m_delta.size(); j++)
		{
			if (std::get<0>(m_delta[j])[0] == 'P')
			{
				ramaneOStare = std::get<0>(m_delta[j]);
				break;
			}
			if (std::get<2>(m_delta[j])[0] == 'P')
			{
				ramaneOStare = std::get<2>(m_delta[j]);
				break;
			}

		}
		//remodificam m_delta
		for (int j = 0; j < m_delta.size(); j++)
		{
			if (std::get<0>(m_delta[j])[0] == 'P')
			    std::get<0>(m_delta[j])=ramaneOStare;
			
			if (std::get<2>(m_delta[j])[0] == 'P')
			    std::get<2>(m_delta[j])=ramaneOStare;
			
		}

		//m_stariFinale
		for (int j = 0; j <m_stariFinale.size(); j++)
			if ((m_stariFinale[j] == m_stari[stariNemarcate[i].first]) || (m_stariFinale[j] == m_stari[stariNemarcate[i].second]))
			{
				m_stariFinale[j][0] = 'P';
			}
		for (int j = 0; j < m_stariFinale.size(); j++)
			if (m_stariFinale[j][0] == 'P')
			{
				ramaneOStare = m_stariFinale[j];
				break;
			}
		for (int j = 0; j < m_stariFinale.size(); j++)
			if (m_stariFinale[j][0] == 'P')
			{
				m_stariFinale[j] = ramaneOStare;
			}

		//m_stari
		for (int j = 0; j < m_stari.size(); j++)
			if ((m_stari[j] == m_stari[stariNemarcate[i].first]) || (m_stari[j] == m_stari[stariNemarcate[i].second]))
			{    
				m_stari[j][0] = 'P';
			}
		
		for (int j = 0; j < m_stari.size(); j++)
			if (m_stari[j][0] == 'P')
			{
				ramaneOStare = m_stari[j];
				break;
			}
		for (int j = 0; j < m_stari.size(); j++)
			if (m_stari[j][0] == 'P')
			{
				m_stari[j]=ramaneOStare;
			}
		//
		//Schimbam litera ca sa mearga si la urmatoarele parcurgeri
		for (int j = 0; j < m_stari.size(); j++)
			if (m_stari[j][0] == 'P')
				m_stari[j][0] = 'A';
		for (int j = 0; j < m_delta.size(); j++)
		{
			if (std::get<0>(m_delta[j])[0] == 'P')
				std::get<0>(m_delta[j])[0] = 'A';
			if (std::get<2>(m_delta[j])[0] == 'P')
				std::get<2>(m_delta[j])[0] = 'A';
		}
		for (int j = 0; j < m_stariFinale.size(); j++)
			if (m_stariFinale[j][0] == 'P')
				m_stariFinale[j][0] = 'A';

	}
	for(int i=0;i<m_stari.size()-1;i++)
		for (int j = 1; j < m_stari.size(); j++)
		{
			if (m_stari[i] == m_stari[j]&&i!=j)
				m_stari.erase(m_stari.begin() + j);
		}
	for(int i=0;i<m_delta.size()-1;i++)
		for (int j = 1; j < m_delta.size(); j++)
		{
			if (m_delta[i] == m_delta[j] && i != j)
				m_delta.erase(m_delta.begin() + j);
		}
	for (int i = 0; i < m_stariFinale.size() - 1; i++)
		for (int j = 1; j < m_stariFinale.size(); j++)
		{
			if (m_stariFinale[i] == m_stariFinale[j] && i != j)
				m_stariFinale.erase(m_stariFinale.begin() + j);
		}
	for (int i = 0; i < m_delta.size(); i++)
	{
		std::get<0>(m_delta[i])[0] = 'P';
		std::get<2>(m_delta[i])[0] = 'P';
	}
	for (int i = 0; i < m_stari.size(); i++)
		m_stari[i][0] = 'P';
	for (int i = 0; i < m_stariFinale.size(); i++)
		m_stariFinale[i][0] = 'P';
	m_stareInit[0] = 'P';
}

void AFD::EliminareStariNeaccesibile()
{
	std::vector<bool> caleVizitata;
	for (int i = 0; i < m_delta.size(); i++)
		caleVizitata.emplace_back(false);
	std::vector<std::pair<std::string, bool>> stariVizitate;
	for (int i = 0; i < m_stari.size(); i++)
		stariVizitate.emplace_back(std::make_pair(m_stari[i], false));

	bool oSchimbare = true;
	bool maiFacemOparcurgere = false;
	int lastIndex;
	std::string stareCurenta = m_stareInit;
	while (oSchimbare == true)
	{
		oSchimbare = false;
		for (int i = 0; i < m_delta.size(); i++)
		{
			if (std::get<0>(m_delta[i]) == stareCurenta)
				if (caleVizitata[i] == false)
				{
					oSchimbare = true;
					maiFacemOparcurgere = true;
					stareCurenta = std::get<2>(m_delta[i]);
					for (int j = 0; j < stariVizitate.size(); j++)
						if (stariVizitate[j].first == stareCurenta)
							stariVizitate[j].second = true;
					lastIndex = i;
				}

			if (i >= m_delta.size() - 1 && maiFacemOparcurgere == true)
			{
				caleVizitata[lastIndex] = true;
				i = 0;
				stareCurenta = m_stareInit;
				maiFacemOparcurgere = false;
			}

		}

	}
	for (int i = 0; i < stariVizitate.size(); i++)
		if (stariVizitate[i].second == false && stariVizitate[i].first != m_stareInit)
		{
			for (int j = 0; j < m_delta.size(); j++)
				if (stariVizitate[i].first == std::get<0>(m_delta[j]))
				{
					m_delta.erase(m_delta.begin() + j);
					j = 0;
				}
			for (int j = 0; j < m_stari.size(); j++)
				if (stariVizitate[i].first == m_stari[j])
					m_stari.erase(m_stari.begin() + j);

		}

}

void AFD::Menu(AFD UnAFD, AFD AltAFD)
{
	int Optiune;
	while (1)
	{
		system("CLS");
		UnAFD.Afisare();
		std::cout << "SELECTEAZA UNA DINTRE URMATOARELE OPTIUNI\n1)Verificare Cuvant\n2)Minimizare\n3)Verificare Cuvant cu AFD-ul Minimizat\n4)Parasire Aplicatie\n";
		std::cin >> Optiune;
		std::string Cuvant;
		switch (Optiune)
		{

		case 1:
			std::cout << "Introduceti un cuvant\n";
			std::cin >> Cuvant;
			Cuvant = UnAFD.VerificareCuvant(Cuvant);
			std::cout << Cuvant;
			system("pause");
			break;
		case 2:
			AltAFD.Minimizare();
			AltAFD.ScrieInFisier("FisierOut.txt");
			std::cout << "Afd-ul minimizat a fost scris in fisierul (FisierOut)";
			system("pause");
			break;
		case 3:
			AltAFD.Minimizare();
			std::cout << "Introduceti un cuvant\n";
			std::cin >> Cuvant;
			Cuvant = AltAFD.VerificareCuvant(Cuvant);
			std::cout << Cuvant;
			system("pause");
			break;

		}
		if (Optiune == 4)
			break;
		if (Optiune != 1 && Optiune != 2&&Optiune!=3)
		{
			std::cout << "Optiunea nu exista! Introduceti o optiune valida";
			system("pause");
		}

	}
}
