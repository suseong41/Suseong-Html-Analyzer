#pragma once

class CHtmlAnalyzer : public IHtmlParserHandler
{
public:
	CHtmlAnalyzer();
	~CHtmlAnalyzer();

	void OnTokenParsed(const ST_HTML_TOKEN& token) override;
	void OnScriptTextParsed(const std::string& text) override;

	bool isBackDoor();
	std::string getDetectionReport();

private:
	void CheckScriptSrc(const std::string& src);
	void ScanRansomeware(const ST_HTML_TOKEN& token);
	void ScanExploitkit(const ST_HTML_TOKEN& token);
	void ScanDownloader(const ST_HTML_TOKEN& token);
	void ScanTrojan(const ST_HTML_TOKEN& token);
	void ScanMiner(const ST_HTML_TOKEN& token);
	void ScanVirus(const ST_HTML_TOKEN& token);
	void ScanWorm(const ST_HTML_TOKEN& token);
	void ScanBackDoor(const ST_HTML_TOKEN& token);

	bool m_backdoorSuspected;
	std::string m_detection;
};