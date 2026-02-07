#include "pch.h"
#include "HtmlHelper.h"
#include "HtmlParser.h"
#include "HtmlAnalyzer.h"

using namespace html_helper;

CHtmlAnalyzer::CHtmlAnalyzer()
{
	m_phishingPattern = false;
	m_backdoor = false;
	m_detection = "";
}
CHtmlAnalyzer::~CHtmlAnalyzer() {}

void CHtmlAnalyzer::OnTokenParsed(const ST_HTML_TOKEN& token)
{
	ScanPhishing(token); // H1xx
	ScanRansomeware(token); // H2xx
	ScanExploitkit(token); // H3xx
	ScanDownloader(token); // H4xx
	ScanTrojan(token); // H5xx
	ScanMiner(token); // H6xx
	ScanVirus(token); // H7xx
	ScanWorm(token); // H8xx
	ScanBackDoor(token); // H9xx


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
}

void CHtmlAnalyzer::OnScriptTextParsed(const std::string& text)
{
	if (text.find("eval(") != std::string::npos)
	{
		Log_Warn("eval() usage detected");
	}

	if (text.find("ls_reserved_all") != std::string::npos ||
		text.find("c99Shell") != std::string::npos ||
		text.find("ByroeNet") != std::string::npos)
	{
		m_backdoor = true;
		m_detection = "[H900] Web Shell found in script Text";
	}
}

void CHtmlAnalyzer::CheckScriptSrc(const std::string& src)
{

}

void CHtmlAnalyzer::ScanPhishing(const ST_HTML_TOKEN& token)
{
	// API Abuse
	if (token.tagName == "form")
	{
		for (UINT64 i = 0; i < token.attr.size(); i++)

		{
			if (token.attr[i].first == "action")
			{
				std::string action = token.attr[i].second;

				action = core::MakeLower(action);

				if (action.find("api.telegram.org") != std::string::npos ||
					action.find("discord.com/api") != std::string::npos ||
					action.find("discordapp.com/api") != std::string::npos)
				{
					m_phishingPattern = true;
					m_detection += "[H101] Phishing API Abuse Detected\n";
				}
			}
		}
	}

	// meta Refresh (Data URI)
	if (token.tagName == "meta")
	{
		bool isRefresh = false;
		std::string content = "";

		for (UINT64 i = 0; i < token.attr.size(); i++)
		{
			std::string key = token.attr[i].first;
			std::string value = token.attr[i].second;

			key = core::MakeLower(key);
			if (key == "http-equiv")
			{
				std::string valueLower = value;
				valueLower = core::MakeLower(valueLower);
				if (valueLower == "refresh")
				{
					isRefresh = true;
				}
			}
			else if (key == "content")
			{
				value = core::MakeLower(value);
			}
			content = value;
		}
		if (isRefresh)
		{
			if (content.find("url=data:") != std::string::npos ||
				content.find("url = data") != std::string::npos)
				{
					m_phishingPattern = true;
					m_detection += "[H102] Meta Refresh Data URI Detected\n";
				}
		}
	}

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
			m_backdoor = true;
			m_detection += "[H901] C99 Shell Command Input Detected\n";
		}

		if (isByroeNet)
		{
			m_backdoor = true;
			m_detection += "[H902] ByroeNet Web Shell Detected\n";
		}
	}
}

bool CHtmlAnalyzer::isPhishingPattern()
{
	return m_phishingPattern;
}

bool CHtmlAnalyzer::isBackDoor()
{
	return m_backdoor;
}

std::string CHtmlAnalyzer::getDetectionReport()
{
	return m_detection;
}
