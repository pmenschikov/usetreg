#include "exceptions.h"
#include "ucontroller.h"


CuController::CuController()
{}

CuController::~CuController()
{
	RegisterMap::iterator it;
	for(it=m_registers.begin(); it!=m_registers.end(); ++it)
	{
		delete it->second;
	}
}

bool CuController::add_register(CRegister *reg)
{
	if( register_by_name(reg->name()) )
	{
		throw ERegAlreadyDefined(reg->name());
	}
	m_registers[reg->name()] = reg;

	return true;
}

bool CuController::add_register_bit(CRegister *reg, CRegisterBit *bit)
{
	CRegister *r = register_by_name(reg->name());
	if( !r )
	{
		throw ERegDefNotFound(reg->name());
	}

	r->add_bit_def(bit);
	return true;
}

CRegister* CuController::register_by_name(const std::string& name)
{
	RegisterMap::iterator it;
	it = m_registers.find(name);

	return it==m_registers.end() ? NULL:it->second;
}
