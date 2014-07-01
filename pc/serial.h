/*
 * Library for serial port
 * Author: Menshikov Pavel, lixrus@gmail.com
 * Date: 19.08.2010
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <string> 

enum SP_BAUDRATE
{
	SP_B9600,
	SP_B19200,
	SP_B57600
};

class CSerialPortSettings
{
	public:
		CSerialPortSettings(const std::string &name,
							SP_BAUDRATE Baud);

	public:
		std::string portname;
		SP_BAUDRATE baud;
};

class CSerialPort
{
	public:
		CSerialPort(const CSerialPortSettings&);
		~CSerialPort();

		bool newSettings(const CSerialPortSettings&);

		int Send(const char*, int);
		int Recv(char*, int);
		bool IsOpen() const;

		bool open();
		bool close();

	private:
		int init();

	private:
		int fd; 
		bool bIsOpen;
		CSerialPortSettings settings;
};

#endif // #ifndef SERIAL_H
