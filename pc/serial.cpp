#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <strings.h>

#include "serial.h"


CSerialPortSettings::CSerialPortSettings(const std::string &name,
										 SP_BAUDRATE Baud)
	: portname(name), baud(Baud)
{

}

CSerialPort::CSerialPort(const CSerialPortSettings &sets)
	: settings(sets)
{
	open();
}

CSerialPort::~CSerialPort()
{
	if(bIsOpen)
	{
		close();
	}
}

int CSerialPort::init()
{
	termios tio;
	speed_t baudrate;

//	tcgetattr(fd, &tio);
	
	bzero(&tio, sizeof(tio));

	switch(settings.baud)
	{
		case SP_B57600: baudrate = B57600; break;
		case SP_B19200: baudrate = B19200; break;
		case SP_B9600: baudrate = B9600; break;
		default: baudrate = B57600; break;
	}

	cfsetispeed(&tio, baudrate);
	cfsetospeed(&tio, baudrate);

	tio.c_cflag |= (CLOCAL | CREAD);
	tio.c_cflag |= CS8;

	tcsetattr(fd, TCSANOW, &tio);

	return 0;
}

bool CSerialPort::IsOpen() const
{
	return bIsOpen;
}

int CSerialPort::Send(const char *buf, int len)
{
	return write(fd, (const void *)(buf), len);
}

int CSerialPort::Recv(char *buf, int len)
{
	return read(fd, (void *)(buf), len);
}

bool CSerialPort::newSettings(const CSerialPortSettings& st)
{
	if(IsOpen())
	{
		this->close();
	}

	settings = st;

	open();
}

bool CSerialPort::open()
{
	fd = ::open(settings.portname.c_str(), 
			O_RDWR | O_NOCTTY | O_NDELAY);
	if(fd==-1)
	{
		bIsOpen = false;
		return false;;
	}

	bIsOpen = true;

	init();
	
	return true;
}

bool CSerialPort::close()
{
	::close(fd);
	bIsOpen = false;
	return true;
}
