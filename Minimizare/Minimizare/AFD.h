#pragma once
#include<vector>
#include<string>
#include<tuple>
class AFD
{
private:
	std::vector<std::string> m_stari;
	std::vector<std::string> m_sigma;
	std::vector<std::tuple<std::string, std::string, std::string>> m_delta;
	std::string m_stareInit;
	std::vector<std::string> m_stariFinale;
protected:
	void Afisare();
	std::string VerificareCuvant(std::string Cuvant);
	void Minimizare();
public:
	AFD(std::vector<std::string> stari, std::vector<std::string> sigma,
		std::vector<std::tuple<std::string, std::string, std::string>> delta,
		std::string stareInit, std::vector<std::string> stariFinale) :
		m_stari(stari), m_sigma(sigma),
		m_delta(delta),
		m_stareInit(stareInit), m_stariFinale(stariFinale)
	{

	}
	AFD CitireDinFisier(const std::string& Fisier);
	void ScrieInFisier(const std::string& Fisier);
	void Menu(AFD UnAFD, AFD AltAFD);
	void EliminareStariNeaccesibile();
	


	


};

