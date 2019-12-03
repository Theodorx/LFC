#pragma once
#include<string>
#include<vector>
class AFN

{
private:
	std::vector<std::string> m_stari;
	std::vector<std::string> m_sigma;
	std::vector<std::pair<std::pair<std::string, std::string>, std::string>> m_delta;
	std::string m_stareInit;
	std::vector<std::string> m_stariFinale;
	std::vector<bool> m_stariAccesibile_Bool;
	
public:
	AFN(std::vector<std::string> stari, std::vector<std::string> sigma,
		std::vector<std::pair<std::pair<std::string, std::string>, std::string>> delta,
		std::string stareInit, std::vector<std::string> stariFinale,std::vector<bool> stariAccesibile_Bool) :
		m_stari(stari), m_sigma(sigma),
		m_delta(delta),
		m_stareInit(stareInit), m_stariFinale(stariFinale),
		m_stariAccesibile_Bool(stariAccesibile_Bool)
	{

	}
	AFN CitireDinFisier(const std::string& Fisier);
	void Afisare();
	std::string VerificareCuvant(std::string Cuvant);
	void Menu(AFN UnAFD);




};

