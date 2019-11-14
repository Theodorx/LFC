#include<iostream>
#include"Gramatica.h"
#include<ctime>
int main()
{
	srand(time(0));
	Gramatica gamaticaCurenta = gamaticaCurenta.Citire_Fisier("FisierGramatica.txt");
	bool state=gamaticaCurenta.Verificare();
	gamaticaCurenta.Afisare();
	if (state == true)
	{
		gamaticaCurenta.Generare();
    }
	else
	{
		std::cout << "Gramatica este gresita";
	}
	system("pause");
	return 0;
}
