#include "pch.h"
#include "HtmlParser.h"

ECODE main(int argc, char* argv[])
{
	if (argc < 2 || 4 < argc)
	{
		Log_Error("usage: ./Suseong-Html-Analyzer <htmlfile> [url]\n");
		return EC_INVALID_ARGUMENT;
	}

	// 분석 시작
	std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

	// 입력 인자 처리
	char* htmlFile = argv[1];
	char* targetUrl = NULL;
	if (3 <= argc)
	{
		targetUrl = argv[2];
	}

	// 분석 종료
	std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
	std::chrono::duration<double, std::milli> elapsed = endTime - startTime;

	Log_Info("Html analysis completed in %.4f ms", elapsed.count());

	return EC_SUCCESS;
}