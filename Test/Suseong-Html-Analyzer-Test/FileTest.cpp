#include "pch.h"
#include <fstream>

// ASSERT -> 반환
// EXPECT -> 계속 실행

TEST(FileTest, ReadSample)
{
	const char* htmlFile = "../../Test/Sample/Sample.html";
	FILE* fp = nullptr;

#ifdef _WIN32
	if (fopen_s(&fp, htmlFile, "rb") != 0 || fp == nullptr)
	{
		FAIL();
		Log_Error("Failed open file: %s", htmlFile);
		return;
	}
#else 
	fp = fopen(htmlFile, "rb");
	if (fp == nullptr)
	{
		FAIL();
		return;
	}
	
#endif

	ASSERT_NE(fp, nullptr);

	fseek(fp, 0, SEEK_END);
	UINT64 fs = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	EXPECT_GT(fs, 0); // empty file

	std::vector<char> buffer(fs);
	UINT64 readCount = fread(buffer.data(), 1, fs, fp);
	EXPECT_EQ(readCount, fs); // file size check

	fclose(fp);

	std::string content(buffer.begin(), buffer.end());
	EXPECT_NE(content.find("Suseong Analyzer"), std::string::npos); // check word
}