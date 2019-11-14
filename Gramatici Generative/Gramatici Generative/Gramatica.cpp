#include "Gramatica.h"
#include<ctime>
Gramatica Gramatica::Citire_Fisier(const std::string& filename)
{
	std::ifstream FisierGramatica(filename);
	std::string neterminale;
	std::string terminale;
	std::string start;
	std::vector<std::pair<std::string, std::string>> productii;
	std::pair<std::string, std::string> Regula;
	FisierGramatica >> neterminale >> terminale >> start;
	while (!FisierGramatica.eof())
	{
		FisierGramatica >> Regula.first >> Regula.second;
		productii.emplace_back(Regula);

	}
	return Gramatica(neterminale, terminale, start, productii);

}

bool Gramatica::Verificare()
{

#pragma region Step 1 Elementele din VN nu se afla in VT

	for (int i = 0; i < m_neterminale.size(); i++)
		for (int j = 0; j < m_terminale.size(); j++)
			if (m_neterminale[i] == m_terminale[j])
				return false;

#pragma endregion

#pragma region Step 2 S se afla in VN;

	for (int i = 0; i < m_start.size(); i++)
		if (m_neterminale.find(m_start[i]) == std::string::npos)
			return false;

#pragma endregion

#pragma region Step 3 Pentru fiecare regula se afla cel putin un neterminal


	for (int i = 0; i < m_productii.size(); i++)
	{
		bool State = false;
		for (int j = 0; j < m_productii[i].first.size(); j++)
			if (m_neterminale.find(m_productii[i].first[j]) != std::string::npos)
				State = true;
		if (State == false)
			return false;
	}

#pragma endregion 

#pragma region  Step 4 Exista cel putin o productie care are in stanga doar S
	bool State = false;
	for (int i = 0; i < m_productii.size(); i++)
		if (m_productii[i].first == m_start)
			State = true;
	if (State == false)
		return false;

#pragma endregion

#pragma region Step 5 Fiecare productie contine doar elemente din VN si VT

	for (int i = 0; i < m_productii.size(); i++)
	{
		for (int j = 0; j < m_productii[i].first.size(); j++)
			if (m_neterminale.find(m_productii[i].first[j]) == std::string::npos &&
				m_terminale.find(m_productii[i].first[j]) == std::string::npos)
				return false;
		for (int j = 0; j < m_productii[i].second.size(); j++)
			if (m_neterminale.find(m_productii[i].second[j]) == std::string::npos &&
				m_terminale.find(m_productii[i].second[j]) == std::string::npos)
				return false;
	}


#pragma endregion

	return true;
}

void Gramatica::Afisare()
{   
	std::cout << "Neterminale:";
	for (int i = 0; i < m_neterminale.size(); i++)
		std::cout << " " << m_neterminale[i];
	std::cout << std::endl;

	std::cout << "Terminale:";
	for (int i = 0; i < m_terminale.size(); i++)
		std::cout << " " << m_terminale[i];
	std::cout << std::endl;
	
	std::cout << "Start: " << m_start << std::endl;

	std::cout << "Productii:";
	for (int i = 0; i < m_productii.size(); i++)
	{
		std::cout << std::endl << m_productii[i].first << "-->" << m_productii[i].second;
	}
	std::cout << std::endl;

}

void Gramatica::Generare()
{
	std::cout << "Introduceti numarul de cuvinte care sa fie generate: ";
	int Nr;
	std::cin >> Nr;

	std::cout << "\nIntroduceti 1 pentru afisarea pasilor intermediari si 0 pentru afisare succinta: ";
	int Opt;
	std::cin >> Opt;
	std::vector<std::pair<std::string,std::string>> applicableRules;

		for (int i = 0; i < Nr; i++)
		{
			std::string currentWord = m_start;
			std::cout << m_start;
			bool loopCondition = true;
			while (loopCondition==true)
			{
				applicableRules.clear();
				for (int j = 0; j < m_productii.size(); j++)
				{
					if (currentWord.find(m_productii[j].first) != std::string::npos)
					{
						applicableRules.push_back(m_productii[j]);

					}
				}
				if (applicableRules.empty() == true)
				{
					loopCondition = false;
					if (Opt == 0)
						std::cout << "-->" << currentWord << std::endl;
					else
						std::cout<<std::endl;
				}
				else
				{
					
					int randomRule_Number = rand() % applicableRules.size();
					int index = currentWord.find(applicableRules[randomRule_Number].first);
					currentWord.replace(index, applicableRules[randomRule_Number].first.size(), applicableRules[randomRule_Number].second);
					if (Opt == 1)
					std::cout << "-->" << currentWord;
				}

			}

		}


}
