#include <iostream>
#include <boost/asio.hpp>

#include <iomanip>
#include "serial.h"

using namespace std;

int main()
{
	CSerialPortSettings ps("/dev/ttyUSB1", SP_B19200);
	CSerialPort port(ps);
	cout << "test" << endl;
	char buff[6];
	buff[0] = 3;
	buff[1] = 0x48;
	buff[2] = 1;
	buff[3] = 1;
	buff[4] = 1;
	buff[5] = 0;
	port.Send(buff,5);
	usleep(100000);
	int read = port.Recv(buff, 2);
	cout << "read : " << read << endl;
	for(int i=0; i<2; i++)
	{
		cout << hex << (short int)buff[i] << ' ';
	}
	cout << endl;
	return 0;
}
