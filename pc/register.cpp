#include <iomanip>
#include "register.h"

#include "exceptions.h"

#define _BV(n) (1<<(n))


CRegister::CRegister(const std::string &name):
	m_name(name),
	m_address(0x00)
{}

CRegister::CRegister(const std::string &name,
		             Address addr):
	m_name(name),
	m_address(addr)
{}

CRegister::~CRegister()
{
	RegisterBits::iterator it;
	for( it=m_bits.begin(); it!=m_bits.end(); ++it)
	{
		delete it->second;
	}
}

std::string CRegister::name() const
{
	return m_name;
}

bool CRegister::add_bit_def(CRegisterBit *bit)
{
	if( m_bits.find(bit->name()) != m_bits.end() )
	{
		throw EBitAlreadyDefined(bit->name());
	}

	m_bits[bit->name()] = bit;
	return true;
}

CRegisterBit* CRegister::get_reg(const std::string& regname)
{
	RegisterBits::iterator it = m_bits.find(regname);
	if( it == m_bits.end() )
	{
		throw EBitDefNotFound(regname);
	}

	return it->second;
}

bool CRegister::set_bit(BitNum bn)
{
	RawData t = m_value;
	m_value |= _BV(bn);;
	return t & _BV(bn) == _BV(bn);
}

bool CRegister::clr_bit(BitNum bn)
{
	RawData t = m_value;
	m_value &= ~_BV(bn);
	return t & _BV(bn) == _BV(bn);
}

bool CRegister::not_bit(BitNum bn)
{
	RawData t = m_value;
	m_value ^= _BV(bn);
	return t & _BV(bn) == _BV(bn);
}

std::ostream& operator<<(std::ostream& os, const CRegister &reg)
{
	os << "Reg(\"";
	os << reg.m_name;
	os << "\",0x";
	os << std::hex;
	os << reg.m_address;
	os << std::dec;
	os << ")";
	return os;
}

CRegister8::CRegister8(const std::string &name,
	Address addr):
	CRegister(name, addr)
{}

Data8Bits CRegister8::value() const
{
	return static_cast<Data8Bits>(m_value);
}

void CRegister8::set_value(Data8Bits v)
{
	m_value = static_cast<RawData>(v);
}

CRegister16::CRegister16(const std::string &name,
		Address addr):
	CRegister(name, addr)
{}

Data16Bits CRegister16::value() const
{
	return static_cast<Data16Bits>(m_value);
}

void CRegister16::set_value(Data16Bits v)
{
	m_value = static_cast<RawData>(v);
}

CRegisterBit::CRegisterBit():
	m_name("default name"),
	m_bitnum(Bit0)
{}

const std::string& CRegisterBit::name() const
{
	return m_name;
}
