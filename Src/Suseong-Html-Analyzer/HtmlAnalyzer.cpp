#include "pch.h"
#include "HtmlParser.h"
#include "HtmlAnalyzer.h"

CHtmlAnalyzer::CHtmlAnalyzer() {}
CHtmlAnalyzer::~CHtmlAnalyzer() {}

void CHtmlAnalyzer::OnTokenParsed(const ST_HTML_TOKEN& token)
{
	if (token.tagName == "script")
	{
		for (UINT64 i = 0; i < token.attr.size(); i++)
		{
			if (token.attr[i].first == "src")
			{
				CheckScriptSrc(token.attr[i].second);
			}
		}
	}

	if (token.tagName == "meta")
	{

	}
}

void CHtmlAnalyzer::OnScriptTextParsed(const std::string& text)
{
	if (text.find("eval(") != std::string::npos)
	{
		Log_Warn("eval() usage detected");
	}
}

void CHtmlAnalyzer::CheckScriptSrc(const std::string& src)
{

}

void CHtmlAnalyzer::ScanRansomeware() {}
void CHtmlAnalyzer::ScanExploitkit() {}
void CHtmlAnalyzer::ScanDownloader() {}
void CHtmlAnalyzer::ScanTrojan() {}
void CHtmlAnalyzer::ScanMiner() {}
void CHtmlAnalyzer::ScanVirus() {}
void CHtmlAnalyzer::ScanWorm() {}
void CHtmlAnalyzer::ScanBackDoor() {}