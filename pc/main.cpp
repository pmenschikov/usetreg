#include <iostream>
#include <boost/asio.hpp>
#include <cstdlib>
#include <string>

#include <iomanip>
#include "serial.h"

using namespace std;

int main(int argc, char **argv)
{
	if( argc < 5 )
	{
		cerr << "usage: " << argv[0] << " USBX what address value" << endl;
		return 0;
	}
	string device("/dev/tty");
	device.append(argv[1]);
	CSerialPortSettings ps(device, SP_B19200);
	CSerialPort port(ps);


	int what = atoi(argv[2]);
	char address = strtol(argv[3], NULL, 16);
	int data = strtol(argv[4], NULL, 16);

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
	
	return 0;
}
