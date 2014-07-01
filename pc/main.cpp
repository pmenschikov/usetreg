#include <iostream>
#include <boost/asio.hpp>
#include <cstdlib>

#include <iomanip>
#include "serial.h"

using namespace std;

int main(int argc, char **argv)
{
	CSerialPortSettings ps("/dev/ttyUSB1", SP_B19200);
	CSerialPort port(ps);

	if( argc < 4 )
	{
		cerr << "usage: " << argv[0] << " what address value" << endl;
		return 0;
	}

	int what = atoi(argv[1]);
	char address = strtol(argv[2], NULL, 16);
	int data = strtol(argv[3], NULL, 16);

	char buff[6];

	buff[0] = (char)(what);
	buff[1] = address;


	if( what == 0 )
	{
		// set 8 bit register
		buff[2] = (char)(data);

		port.Send(buff, 3);
	}
	else if( what == 1 )
	{
		// set 16 bit register
		buff[2] = (char)(data);
		buff[3] = (char)(data>>8);

		port.Send(buff, 4);
	}
	
	cout << endl;
	return 0;
}
