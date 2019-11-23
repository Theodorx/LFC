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
	std::vector<std::pair<std::pair<std::string, std::string>, std::string>> delta;
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
			delta.emplace_back(std::make_pair(std::make_pair(Aux, Aux1), Aux2));

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
		std::cout << "\n" << m_delta[i].first.first << " " << m_delta[i].first.second << " " << m_delta[i].second;
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
			if (stareCurenta == m_delta[j].first.first && Cuvant[i] == m_delta[j].first.second[0])
			{
				stareCurenta = m_delta[j].second;
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

void AFD::Menu(AFD UnAFD)
{
	std::string Optiune = "";
	while (1)
	{
		system("CLS");
		UnAFD.Afisare();
		std::cout << "SELECTEAZA UNA DINTRE URMATOARELE OPTIUNI\n1)Verificare Cuvant\n2)Parasire Aplicatie\n";
		std::cin >> Optiune;
		if (Optiune == "2")
			break;
		if (Optiune != "1")
		{
			std::cout << "Optiunea nu exista! Introduceti o optiune valida";
			system("pause");
		}
		else
		{
			std::cout << "Introduceti un cuvant\n";
			std::string Cuvant;
			std::cin >> Cuvant;
			Cuvant = VerificareCuvant(Cuvant);
			std::cout << Cuvant;
			system("pause");
		}
	}
}
