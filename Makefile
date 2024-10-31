# Project Name
NAME = webserv

# Compiler and Flags
CCXX = c++
PROCCESSORS = -j 4
DEBUG = -g3
FLAGS =-std=c++98 $(DEBUG) -Wall -Wextra -Werror 
RM = rm -r

# Directories
OBJECTS = objects
SOURCES = sources
INCLUDES = includes

# Subdirectories for Source and Header files
PARSING_SUBDIRS = Config Request
VALIDATION_SUBDIRS = Config Request Response

SUBDIRS = CGI Builder ConfigFile Errors Filler Handler \
		  Http Listener Parser $(addprefix Parsing/,$(PARSING_SUBDIRS)) Request \
		  Response Server Socket $(addprefix Validation/,$(VALIDATION_SUBDIRS)) Validator

#PUT IN ALPHABETICAL ORDER
# Header Files (without paths)
BUILDER_HEADERS = ResponseLineBuilder.hpp  ResponseHeadersBuilder.hpp ResponseBodyBuilder.hpp ResponseMethodBodyBuilder.hpp ResponseErrorBodyBuilder.hpp \
				  ResponseTreeBodyBuilder.hpp ResponseRedirectionBodyBuilder.hpp

CGI_HEADERS = CgiHandler.hpp
CONFIG_HEADERS = ConfigError.hpp ConfigListen.hpp ConfigPath.hpp ConfigRoute.hpp ConfigServer.hpp \
				 ConfigTree.hpp ConfigValue.hpp ConfigCgi.hpp

ERROR_HEADERS = ListenerErrors.hpp ServerErrors.hpp SocketErrors.hpp
FILLER_HEADERS = ConfigFiller.hpp
HANDLER_HEADERS = FileHandler.hpp RequestHandler.hpp ResponseHandler.hpp
HTTP_HEADERS = HttpBody.hpp HttpElement.hpp HttpConfig.hpp HttpHeaders.hpp
LISTENER_HEADERS = Listener.hpp
PARSER_HEADERS =  ConfigParser.hpp RequestParser.hpp ParserElement.hpp
CONFIG_PARSING_HEADERS = ConfigFileBlockParsing.hpp ConfigFileParsing.hpp ConfigFileRouteParsing.hpp ConfigFileServerParsing.hpp ConfigFinalParsing.hpp \
						 ConfigParsing.hpp ConfigPreParsing.hpp

REQUEST_PARSING_HEADERS = DeleteRequestBodyParsing.hpp GetRequestBodyParsing.hpp PostRequestBodyParsing.hpp RequestBodyParsing.hpp RequestHeadersParsing.hpp \
						 RequestLineParsing.hpp RequestParsing.hpp

REQUEST_HEADERS = HttpRequest.hpp Incomplete_Request.hpp RequestInformation.hpp RequestLine.hpp
RESPONSE_HEADERS = HttpResponse.hpp ResponseInformation.hpp ResponseLine.hpp
SERVER_HEADERS = Server.hpp
SOCKET_HEADERS = Socket.hpp
VALIDATION_CONFIG_HEADERS = ConfigFileBlockValidation.hpp ConfigFileEntryValidation.hpp ConfigFileObjectValidation.hpp ConfigFileRouteIndexValidation.hpp ConfigFileRouteMethodValidation.hpp \
							ConfigFileRouteRedirectValidation.hpp ConfigFileRouteRoutesValidation.hpp ConfigFileRouteTreeValidation.hpp ConfigFileRouteUploadValidation.hpp  ConfigFileRouteValidation.hpp \
							ConfigFileServerBodySizeValidation.hpp ConfigFileServerDomainValidation.hpp ConfigFileServerErrorValidation.hpp ConfigFileServerHeaderValidation.hpp ConfigFileServerListenValidation.hpp \
							ConfigFileServerRouteValidation.hpp ConfigFileServerValidation.hpp ConfigFinalValidation.hpp ConfigPreValidation.hpp ConfigFileRouteCgiValidation.hpp

VALIDATION_REQUEST_HEADERS = DeleteRequestHeadersValidation.hpp DeleteRequestBodyValidation.hpp GetRequestBodyValidation.hpp GetRequestHeadersValidation.hpp PostRequestBodyValidation.hpp \
							 PostRequestHeadersValidation.hpp  RequestBodyValidation.hpp RequestHeadersValidation.hpp RequestLineValidation.hpp

VALIDATION_RESPONSE_HEADERS = ResponseValidation.hpp
VALIDATOR_HEADERS = ConfigValidator.hpp RequestValidator.hpp ResponseValidator.hpp
# Combine Header Files
PARSING_HEADERS = $(CONFIG_PARSING_HEADERS) $(REQUEST_PARSING_HEADERS)
VALIDATION_HEADERS = $(VALIDATION_CONFIG_HEADERS) $(VALIDATION_REQUEST_HEADERS) $(VALIDATION_RESPONSE_HEADERS)

HEADERS = $(CGI_HEADERS) $(BUILDER_HEADERS) $(CONFIG_HEADERS) $(ERROR_HEADERS) $(FILLER_HEADERS) $(HANDLER_HEADERS) \
		  $(HTTP_HEADERS) $(LISTENER_HEADERS) $(PARSER_HEADERS) $(PARSING_HEADERS) $(REQUEST_HEADERS) \
		  $(RESPONSE_HEADERS) $(SERVER_HEADERS) $(SOCKET_HEADERS) $(VALIDATION_HEADERS) $(VALIDATOR_HEADERS)

CSTYLE_HEADERS = Project.hpp CStyle/Colors.hpp CStyle/Enumerations.hpp CStyle/ErrorMessages.hpp CStyle/Keys.hpp \
				 CStyle/Libraries.hpp CStyle/Macros.hpp
# Generate Source Files by replacing .hpp with .cpp
SUBDIR_SRCS = $(patsubst %.hpp,%.cpp,$(HEADERS))

# Include main.cpp as it's not in a subdirectory
MAIN = main.cpp
SRCS = $(SUBDIR_SRCS) $(MAIN)

# Use vpath to search for sources and headers in the respective subdirectories
vpath %.cpp $(addprefix $(SOURCES)/,$(SUBDIRS)) $(SOURCES)
vpath %.hpp $(addprefix $(INCLUDES)/,$(SUBDIRS))

# Generate Object File Paths
OBJ_SUBDIRS = $(patsubst %.cpp,$(OBJECTS)/%.o,$(SUBDIR_SRCS))
OBJ_MAIN = $(patsubst %.cpp,$(OBJECTS)/%.o,$(MAIN))
OBJ = $(OBJ_SUBDIRS) $(OBJ_MAIN)

#Rules
all: $(NAME)

$(NAME): $(OBJ) $(HEADERS) $(addprefix $(INCLUDES)/,$(CSTYLE_HEADERS))
	$(CCXX) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJECTS)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CCXX) $(FLAGS) -c $< -o $@

clean:
	@test -d $(OBJECTS) && $(RM) -v $(OBJECTS) || echo "$(OBJECTS) does not exist, skipping."

fclean: clean
	@test -f $(NAME) && $(RM) -v $(NAME) || echo "$(NAME) does not exist, skipping."


re: fclean
	@make all $(PROCCESSORS) --no-print-directory 2>/dev/null

.PHONY: all clean fclean re

