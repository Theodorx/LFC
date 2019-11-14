#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
class Gramatica
{
private:
	 std::string m_neterminale;
	 std::string m_terminale;
	 std::string m_start;
	std::vector<std::pair<std::string, std::string>> m_productii;
public:
	
	Gramatica(std::string neterminale,  std::string terminale, std::string start, std::vector<std::pair<std::string, std::string>> productii) :
		m_neterminale(neterminale), m_terminale(terminale), m_start(start), m_productii(productii)
	{

	}	
	Gramatica Citire_Fisier(const std::string& filename);
	bool Verificare();
	void Afisare();
	void Generare();


};
