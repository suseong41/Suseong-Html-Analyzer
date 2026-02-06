#include "pch.h"
#include "../../Src/Suseong-Html-Analyzer/HtmlParser.h"
#include "../../Src/Suseong-Html-Analyzer/HtmlAnalyzer.h"

// EXPECT_EQ();
// ASEERT_EQ();

class HtmlParserTest : public IHtmlParserHandler
{
public:
    std::vector<ST_HTML_TOKEN> capToken;
    std::vector<std::string> capScript;
    void OnTokenParsed(const ST_HTML_TOKEN& token) override
    {
        capToken.push_back(token);
    }
    void OnScriptTextParsed(const std::string& text) override
    {
        capScript.push_back(text);
    }

private:
};
/*
TEST(ScanTest, Randsomeware)
{

}

TEST(ScanTest, ExploitKit)
{

}

TEST(ScanTest, Downloader)
{

}

TEST(ScanTest, Trojan)
{

}

TEST(ScanTest, Miner)
{

}

TEST(ScanTest, Worm)
{

}

TEST(ScanTest, BackDoor)
{

}
*/