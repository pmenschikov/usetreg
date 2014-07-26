#include "register.h"

#define _BV(n) (1<<(n))


CRegister::CRegister(const std::string &name):
	m_name(name)
{}

std::string CRegister::name() const
{
	return m_name;
}

CRegister::CRegister(const std::string &name,
		RawData data):
	m_name(name),
	m_value(data)
{}

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

CRegister8::CRegister8(const std::string& name):
	CRegister(name, RawData())
{}

CRegister8::CRegister8(const std::string &name,
	const Data8Bits v):
	CRegister(name, static_cast<RawData>(v))
{}


CRegister16::CRegister16(const std::string &name):
	CRegister(name, RawData())
{}

CRegister16::CRegister16(const std::string &name,
		const Data16Bits v):
	CRegister(name, static_cast<RawData>(v))
{}

