#ifndef __UCONTROLLER_H__
#define __UCONTROLLER_H__

#include <map>

#include "register.h"

class CuController
{
	public:
		CuController();
		~CuController();

		/*
		 * set_bit
		 * clr_bit
		 * toggle_bit
		 */
		bool set_bit(const std::string&);
		bool set_bit(const CRegisterBit*);
		bool clr_bit(const std::string&);
		bool clr_bit(const CRegisterBit*);
		bool toggle_bit(const std::string&);
		bool toggle_bit(const CRegister*);

		bool add_register(CRegister*);
		bool add_register_bit(CRegister*, CRegisterBit*);
		bool add_register_bit(const std::string&, CRegisterBit*);

	protected:
		typedef std::map<std::string, CRegister*> RegisterMap;

	protected:
		CRegister* register_by_name(const std::string&);

	protected:
		RegisterMap m_registers;
};

#endif // __UCONTROLLER_H__
