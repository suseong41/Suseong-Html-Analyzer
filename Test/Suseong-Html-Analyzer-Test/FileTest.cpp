#include "pch.h"
#include "../../Src/Suseong-Html-Analyzer/HtmlLoader.h"

// ASSERT -> 반환
// EXPECT -> 계속 실행

TEST(FileTest, ReadSample)
{
	const char* path = "../../Test/Sample/Sample.html";
	
	std::string html = HtmlLoad(path);
	EXPECT_NE(html.find("Suseong Analyzer"), std::string::npos); // check word
}