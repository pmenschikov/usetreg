#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <stdexcept>
#include <string>

class EuSetReg: public std::exception
{};

class EBitDefNotFound: public EuSetReg,
	                   public std::runtime_error
{
	public:
		EBitDefNotFound(const std::string);
};

class EBitAlreadyDefined: public EuSetReg,
                          public std::runtime_error
{
	public:
		EBitAlreadyDefined(const std::string);
};

class ERegDefNotFound: public EuSetReg,
                       public std::runtime_error
{
	public:
		ERegDefNotFound(const std::string&);
};

class ERegAlreadyDefined: public EuSetReg,
                       public std::runtime_error
{
	public:
		ERegAlreadyDefined(const std::string&);
};
#endif // __EXCEPTIONS_H__
