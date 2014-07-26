#ifndef __register_h__
#define __register_h__

#include <string>

typedef unsigned int BitNum;
typedef unsigned char Data8Bits;
typedef unsigned short Data16Bits;

enum Bits
{
	Bit0 = 0,
	Bit1 = 1,
	Bit2 = 2,
	Bit3 = 3,
	Bit4 = 4,
	Bit5 = 5,
	Bit6 = 6,
	Bit7 = 7
};

class CRegisterBit
{
	public:
		CRegisterBit(const std::string &name,
				Bits bn);
		std::string& name() const;
	private:
		std::string m_name;
		Bits m_bitnum;
};

class CRegister
{
	public:
		typedef unsigned int RawData;
	public:
		CRegister(const std::string &name);

		bool set_bit(BitNum bit);
		bool clr_bit(BitNum bit);
		bool not_bit(BitNum bit);

		std::string name() const;

	protected:
		explicit CRegister(const std::string &name,
				RawData data = 0);

	protected:
		std::string m_name;
		RawData m_value;
};

class CRegister8: public CRegister
{
	public:
		CRegister8(const std::string &name);
		CRegister8(const std::string &name,
		              const Data8Bits v);

};

class CRegister16: public CRegister
{
	public:
		CRegister16(const std::string &name);
		CRegister16(const std::string &name,
		              const Data16Bits v);

};


#endif // __register_h__
