#include "pch.h"
#include "HtmlParser.h"
#include "HtmlAnalyzer.h"

CHtmlAnalyzer::CHtmlAnalyzer()
{
	m_backdoorSuspected = false;
	m_detection = "";
}
CHtmlAnalyzer::~CHtmlAnalyzer() {}

void CHtmlAnalyzer::OnTokenParsed(const ST_HTML_TOKEN& token)
{
	ScanBackDoor(token);
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

	if (text.find("ls_reserved_all") != std::string::npos ||
		text.find("c99Shell")!=std::string::npos ||
		text.find("ByroeNet") != std::string::npos)
	{
		m_backdoorSuspected = true;
		m_detection = "[Script] Web Shell found in script Text";
	}
}

void CHtmlAnalyzer::CheckScriptSrc(const std::string& src)
{

}

void CHtmlAnalyzer::ScanRansomeware(const ST_HTML_TOKEN& token) {}
void CHtmlAnalyzer::ScanExploitkit(const ST_HTML_TOKEN& token) {}
void CHtmlAnalyzer::ScanDownloader(const ST_HTML_TOKEN& token) {}
void CHtmlAnalyzer::ScanTrojan(const ST_HTML_TOKEN& token) {}
void CHtmlAnalyzer::ScanMiner(const ST_HTML_TOKEN& token) {}
void CHtmlAnalyzer::ScanVirus(const ST_HTML_TOKEN& token) {}
void CHtmlAnalyzer::ScanWorm(const ST_HTML_TOKEN& token) {}
void CHtmlAnalyzer::ScanBackDoor(const ST_HTML_TOKEN& token)
{
	if (token.tagName == "input")
	{
		bool isHidden = false;
		bool isNameAct = false;
		bool isSuspiciousValue = false;
		bool isByroeNet = false;

		for (UINT64 i = 0; i < token.attr.size(); i++)
		{
			std::string key = token.attr[i].first;
			std::string value = token.attr[i].second;

			if (key == "type" && value == "hidden") isHidden = true;
			else if (key == "name" && value == "act") isNameAct = true;
			else if (key == "value" && (value == "cmd" || value == "uploade" || value == "mkfile")) isSuspiciousValue = true;

			if (key == "name")
			{
				if (value == "_cmd" || value == "_cwd" || value == "_act")
				{
					isByroeNet = true;
				}
			}
		}

		if (isHidden && isNameAct && isSuspiciousValue)
		{
			m_backdoorSuspected = true;
			m_detection = "[BackDoor] C99 Shell Command Input Detected\n";
		}

		if (isByroeNet)
		{
			m_backdoorSuspected = true;
			m_detection = "[BackDoor] ByroeNet Web Shell Detected\n";
		}
	}
}

bool CHtmlAnalyzer::isBackDoor()
{
	return m_backdoorSuspected;
}

std::string CHtmlAnalyzer::getDetectionReport()
{
	return m_detection;
}
