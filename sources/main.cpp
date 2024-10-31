#include "../includes/Http/HttpElement.hpp"
#include "../includes/Listener/Listener.hpp"
#include "../includes/Parser/ParserElement.hpp"
#include "../includes/Project.hpp"

void	signalHandler(int signal)
{
	if (signal == SIGINT)
		std::cout << TCYAN << KILLMSG << TRESET << std::endl;
}

int	main(int argc, char *argv[])
{
	ParserElement parser;
	std::string inputFilePath;

	if (argc == 0 || 2 < argc)
	{
		std::string error = ARGCOUNT;
		parser.printError(error + "\n" + USAGE);
		return (1);
	}
	else if (argc == 1)
		inputFilePath = DEFAULTSERVERCONFIG;
	else
		inputFilePath = argv[1];
	/* INIT HTTPCONFIG */
	HttpConfig httpConfig(inputFilePath);
	httpConfig.filePath.setPath(inputFilePath);
	if (!parser.configParser.parseConfig(httpConfig))
		return (parser.printError(PARSINGCONF), 1);
	std::cout << TGREEN << "File path valid!!!" << TRESET << std::endl;

	/* INIT LISTENER */
	Listener listener;

	std::signal(SIGINT, signalHandler);
	std::signal(SIGPIPE, SIG_IGN);
	listener.httpFullConfig = httpConfig;
	listener.init();
	listener.close_all();
	return (0);
}