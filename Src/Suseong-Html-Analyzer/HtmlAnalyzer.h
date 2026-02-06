#pragma once

class CHtmlAnalyzer : public IHtmlParserHandler
{
public:
	CHtmlAnalyzer();
	~CHtmlAnalyzer();

	void OnTokenParsed(const ST_HTML_TOKEN& token) override;
	void OnScriptTextParsed(const std::string& text) override;
private:
	void CheckScriptSrc(const std::string& src);
	void ScanRansomeware();
	void ScanExploitkit();
	void ScanDownloader();
	void ScanTrojan();
	void ScanMiner();
	void ScanVirus();
	void ScanWorm();
	void ScanBackDoor();
};