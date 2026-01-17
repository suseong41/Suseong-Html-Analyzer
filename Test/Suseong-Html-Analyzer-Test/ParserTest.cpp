#include "pch.h"
#include "../../Src/Suseong-Html-Analyzer/HtmlParser.h"

class HtmlParserTest : public IHtmlParserHandler
{
public:
	std::vector<ST_HTML_TOKEN> capturedTokens;
	std::vector<std::string> capturedScripts;
	void OnTokenParsed(const ST_HTML_TOKEN& token) override
	{
		capturedTokens.push_back(token);
	}
	void OnScriptTextParsed(const std::string& text) override
	{
		capturedScripts.push_back(text);
	}

private:
};

TEST(ParserTest, LowerCase)
{
	CHtmlParser parser;
	HtmlParserTest test;
	parser.SetHandler(&test);

	std::string html = "<DIV><div >"; // 대문자, 공백
	parser.Parse(html.c_str(), html.length());

	ASSERT_EQ(test.capturedTokens.size(), 2);
	EXPECT_EQ(test.capturedTokens[0].tagName, "div");
	EXPECT_FALSE(test.capturedTokens[0].isClosing);

	EXPECT_EQ(test.capturedTokens[1].tagName, "div");
	EXPECT_TRUE(test.capturedTokens[1].isClosing);
}