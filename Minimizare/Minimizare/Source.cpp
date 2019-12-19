#include<iostream>
#include"AFD.h"
int main()
{
	AFD UnAFD = UnAFD.CitireDinFisier("Automat finit File.txt");
	AFD AltAFD = AltAFD.CitireDinFisier("Automat finit File.txt");
	AltAFD.EliminareStariNeaccesibile();
	UnAFD.Menu(AltAFD);
	return 0;

}