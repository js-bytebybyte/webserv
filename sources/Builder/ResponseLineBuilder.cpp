#include "../../includes/Builder/ResponseLineBuilder.hpp"

/*PUBLIC FUNCTIONS*/

/* Cannonical form*/
ResponseLineBuilder::ResponseLineBuilder(void) : http(PROTOCOL), statusCode(UNDEFINED), reason(""), statusLine("")
{
}

ResponseLineBuilder::ResponseLineBuilder(const ResponseLineBuilder &other)
{
	*this = other;
}

ResponseLineBuilder &ResponseLineBuilder::operator=(const ResponseLineBuilder &other)
{
	if (this != &other)
	{
		http = other.http;
		statusCode = other.statusCode;
		reason = other.reason;
		statusLine = other.statusLine;
	}
	return (*this);
}

ResponseLineBuilder::~ResponseLineBuilder(void)
{
}

/*
	Function to handle the response
*/
void ResponseLineBuilder::buildResponseLine(HttpElement &element)
{
	std::stringstream ss;

	buildHttp();
	buildStatusCode(*element.request);
	buildReason();
    ss << statusCode;
	element.response->statusLine.setHttp(http);
	element.response->statusLine.setStatusCode(statusCode);
	element.response->statusLine.setReason(reason);
    statusLine = http + " " + ss.str() + " " + reason + "\r\n";
	element.response->statusLine.setFullStatus(statusLine);
}

/*PRIVATE FUNCTIONS*/

/*
	Helper functions
*/
void ResponseLineBuilder::buildHttp(void)
{
	http = "HTTP/1.1";
}

void ResponseLineBuilder::buildStatusCode(const HttpRequest &request)
{
	statusCode = request.info.getStatus();
}

std::string ResponseLineBuilder::buildInformational(void) const
{
	std::string reason;
	if (CONTINUE == statusCode)
		reason = "Continue";
	else if (SWITCHING_PROTOCOLS == statusCode)
		reason = "Switching Protocols";
	else if (PROCESSING == statusCode)
		reason = "Processing";
	else if (EARLY_HINTS == statusCode)
		reason = "Early Hints";
	return (reason);
}

std::string ResponseLineBuilder::buildSuccess(void) const
{
	std::string reason;
	if (OK == statusCode)
		reason = "OK";
	else if (CREATED == statusCode)
		reason = "Created";
	else if (ACCEPTED == statusCode)
		reason = "Accepted";
	else if (NON_AUTHORITATIVE_INFO == statusCode)
		reason = "Non-Authoritative Information";
	else if (NO_CONTENT == statusCode)
		reason = "No Content";
	else if (RESET_CONTENT == statusCode)
		reason = "Reset Content";
	else if (PARTIAL_CONTENT == statusCode)
		reason = "Partial Content";
	else if (MULTI_STATUS == statusCode)
		reason = "Multi-Status";
	else if (ALREADY_REPORTED == statusCode)
		reason = "Already Reported";
	else if (IM_USED == statusCode)
		reason = "IM Used";
	return (reason);
}

std::string ResponseLineBuilder::buildRedirection(void) const
{
	std::string reason;
	if (MULTIPLE_CHOISE == statusCode)
		reason = "Multiple Choice";
	else if (MOVED_PERMANENT == statusCode)
		reason = "Moved Permanently";
	else if (FOUND == statusCode)
		reason = "Found";
	else if (SEE_OTHER == statusCode)
		reason = "See Other";
	else if (NOT_MODIFIED == statusCode)
		reason = "Not Modified";
	else if (USE_PROXY == statusCode)
		reason = "Use Proxy";
	else if (SWITCH_PROXY == statusCode)
		reason = "Switch Proxy";
	else if (TEMPORARY_REDIRECT == statusCode)
		reason = "Temporary Redirect";
	else if (PERMANENT_REDIRECT == statusCode)
		reason = "Permanent Redirect";
	return (reason);
}

std::string ResponseLineBuilder::buildClientError(void) const
{
	std::string reason;
	if (BAD_REQUEST == statusCode)
		reason = "Bad Request";
	else if (UNAUTHORIZED == statusCode)
		reason = "Unauthorized";
	else if (PAYMENTREQUIRED == statusCode)
		reason = "Payment Required";
	else if (FORBIDDEN == statusCode)
		reason = "Forbidden";
	else if (NOTFOUND == statusCode)
		reason = "Not Found";
	else if (METHOD_NOT_ALLOWED == statusCode)
		reason = "Method Not Allowed";
	else if (NOT_ACCEPTABLE == statusCode)
		reason = "Not Acceptable";
	else if (PROXY_AUTHENTICATION_REQUIRED == statusCode)
		reason = "Proxy Authentication Required";
	else if (REQUEST_TIMEOUT == statusCode)
		reason = "Request Timeout";
	else if (CONFILCT == statusCode)
		reason = "Conflict";
	else if (GONE == statusCode)
		reason = "Gone";
	else if (LENGTH_REQUIRED == statusCode)
		reason = "Length Required";
	else if (PRECONDITION_FAILED == statusCode)
		reason = "Precondition Failed";
	else if (PAYLOAD_TOO_LARGE == statusCode)
		reason = "Payload Too Large";
	else if (URI_TOO_LONG == statusCode)
		reason = "URI Too Long";
	else if (UNSUPPORTED_MEDIA_TYPE == statusCode)
		reason = "Unsupported Media Type";
	else if(RANGE_NOT_SATISFIABLE == statusCode)
		reason = "Range Not Satisfiable";
	else if (EXPECTATION_FAILED == statusCode)
		reason = "Expectation Failed";
	else if (IM_A_TEAPOT == statusCode)
		reason = "I'm a teapot";
	else if (MISDIRECTED_REQUEST == statusCode)
		reason = "Misdirected Request";
	else if (UNPROCESSABLE_ENTITY == statusCode)
		reason = "Unprocessable Entity";
	else if (LOCKED == statusCode)
		reason = "Locked";
	else if (FAILED_DEPENDENCY == statusCode)
		reason = "Failed Dependency";
	else if (TOO_EARLY == statusCode)
		reason = "Too Early";
	else if (UPGRADE_REQUIRED == statusCode)
		reason = "Upgrade Required";
	else if (PRECONDITION_REQUIRED == statusCode)
		reason = "Precondition Required";
	else if (TOO_MANY_REQUESTS == statusCode)
		reason = "Too Many Requests";
	else if (REQUEST_HEADER_FIELDS_TOO_LARGE == statusCode)
		reason = "Request Header Fields Too Large";
	else if (UNAVAILABLE_FOR_LEGAL_REASONS == statusCode)
		reason = "Unavailable For Legal Reasons";
	return (reason);
}

std::string ResponseLineBuilder::buildServerError(void) const
{
	std::string reason;
	if (INTERNAL_SERVER_ERROR == statusCode)
		reason = "Internal Server Error";
	else if (NOT_IMPLEMENTED == statusCode)
		reason = "Not Implemented";
	else if (BAD_GATEWAY == statusCode)
		reason = "Bad Gateway";
	else if (SERVICE_UNAVAILABLE == statusCode)
		reason = "Service Unavailable";
	else if (GATEWAY_TIMEOUT == statusCode)
		reason = "Gateway Timeout";
	else if (HTTP_VERSION_NOT_SUPPORTED == statusCode)
		reason = "HTTP Version Not Supported";
	else if (VARIANT_ALSO_NEGOTIATES == statusCode)
		reason = "Variant Also Negotiates";
	else if (INSUFFICIENT_STORAGE == statusCode)
		reason = "Insufficient Storage";
	else if (LOOP_DETECTED == statusCode)
		reason = "Loop Detected";
	else if (NOT_EXTENDED == statusCode)
		reason = "Not Extended";
	else if (NETWORK_AUTHENTICATION_REQUIRED == statusCode)
		reason = "Network Authentication Required";
	return (reason);
}

void ResponseLineBuilder::buildReason(void)
{
	if (CONTINUE <= statusCode && statusCode <= EARLY_HINTS)
		reason = buildInformational();
	else if (OK <= statusCode && statusCode <= IM_USED)
		reason = buildSuccess();
	else if (MULTIPLE_CHOISE <= statusCode && statusCode <= PERMANENT_REDIRECT)
		reason = buildRedirection();
	else if (BAD_REQUEST <= statusCode
		&& statusCode <= UNAVAILABLE_FOR_LEGAL_REASONS)
		reason = buildClientError();
	else if (INTERNAL_SERVER_ERROR <= statusCode
		&& statusCode <= NETWORK_AUTHENTICATION_REQUIRED)
		reason = buildServerError();
	else
		reason = "Undefined";
}