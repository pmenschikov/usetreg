#include "exceptions.h"

using std::runtime_error;

EBitDefNotFound::EBitDefNotFound(const std::string what):
	std::runtime_error(what)
{}

EBitAlreadyDefined::EBitAlreadyDefined(const std::string what):
	std::runtime_error(what)
{}

ERegAlreadyDefined::ERegAlreadyDefined(const std::string &what):
	runtime_error(what)
{}

ERegDefNotFound::ERegDefNotFound(const std::string &what):
	runtime_error(what)
{}
