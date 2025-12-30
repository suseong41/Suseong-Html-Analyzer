#include "pch.h"

ECODE main(int argc, char* argv[])
{
	if (argc < 2 || 4 < argc)
	{
		printf("usage: ./Suseong-Html-Analyzer <htmlfile> [url]\n");
		return EC_INVALID_ARGUMENT;
	}

	printf("Hello World!\n");

	char* htmlFile = argv[1];
	char* targetUrl = NULL;
	if (3 <= argc)
	{
		targetUrl = argv[2];
	}

	return EC_SUCCESS;
}