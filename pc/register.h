#ifndef __register_h__
#define __register_h__

#include <string>
#include <map>

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
		CRegisterBit();
		CRegisterBit(const std::string &name,
				Bits bn);
		const std::string& name() const;
	private:
		std::string m_name;
		Bits m_bitnum;
};

class CRegister
{
	public:
		typedef unsigned int RawData;
		typedef unsigned int Address;
		
	public:
		CRegister(const std::string &name);
		CRegister(const std::string &name, Address&);
		~CRegister();

		bool add_bit_def(CRegisterBit*);

		bool set_bit(BitNum bit);
		bool clr_bit(BitNum bit);
		bool not_bit(BitNum bit);

		std::string name() const;

	protected:
		CRegisterBit* get_reg(const std::string&);

	protected:
		typedef std::map<std::string, CRegisterBit*> RegisterBits;

	protected:
		std::string m_name;
		RawData m_value;
		Address m_address;
		RegisterBits m_bits;
};

class CRegister8: public CRegister
{
	public:
		CRegister8(const std::string &name,
		           Address addr);

		Data8Bits value() const;
		void set_value(Data8Bits v);

};

class CRegister16: public CRegister
{
	public:
		CRegister16(const std::string &name,
		            Address addr);

		Data16Bits value() const;
		void set_value(Data16Bits v);
};


#endif // __register_h__
