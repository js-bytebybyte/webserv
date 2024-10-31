#include "../../includes/Validator/ResponseValidator.hpp"

/* Cannonical form*/
ResponseValidator::ResponseValidator(void) : _responseValidation(), status_code(UNDEFINED)
{
}

ResponseValidator::ResponseValidator(const ResponseValidator &other)
{
	*this = other;
}

ResponseValidator &ResponseValidator::operator=(const ResponseValidator &other)
{
	if (this != &other)
	{
		_responseValidation = other._responseValidation;
		status_code = other.status_code;
	}
	return (*this);
}

ResponseValidator::~ResponseValidator(void)
{
}

bool ResponseValidator::checker(HttpRequest &_request, ConfigServer &cfg)
{
	std::string Uri = _request.requestLine.getUri();
	if (!_responseValidation.check_in(_request, cfg.locationsVector))
	{
		std::cout << std::endl << TRED << " [CFG_SERVRE : CHECK_IN] FALSE " << Uri << TRESET << std::endl;
	}
	else
		std::cout << std::endl << TGREEN << " [CFG_SERVRE : CHECK_IN] TRUE " << Uri << TRESET << std::endl;
	if (!_responseValidation.check_out(_request, cfg.locationsVector))
	{
		std::cout << std::endl << TRED << " [CFG_SERVRE : CHECK_OUT] FALSE " << Uri << TRESET << std::endl;
	}
	else
		std::cout << std::endl << TGREEN << " [CFG_SERVRE : CHECK_OUT] TRUE " << Uri << TRESET << std::endl;
	return (true);
}

ResponseValidation ResponseValidator::getValidator(void) const
{
	return (_responseValidation);
}