#include <iostream>
#include <boost/asio.hpp>
#include <cstdlib>
#include <string>

#include <unistd.h>

#include <iomanip>
#include "ucontroller.h"
#include "exceptions.h"

using namespace std;

int main(int argc, char **argv)
{
	CuController controller;
	cout << controller << endl;
	CRegister *reg = new CRegister8(string("TCCR1A"), CRegister::Address(0x43));
	controller.add_register(reg);
	try
	{
		controller.add_register(reg);
	}
	catch( ERegAlreadyDefined &e)
	{
		cout << "Register " << e.what() << " already defined" << endl;
	}
	cout << controller << endl;

	return 0;
}
