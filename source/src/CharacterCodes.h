#pragma once

#include <string>
#include <Windows.h>
#include <iostream>

#define UTF8(mbytes) MBytesToUTF8((mbytes))
#define MBytes(utf8) UTF8ToMBytes((utf8))

std::wstring MBytesToWString(const char* lpcszString);
std::string WStringToMBytes(const wchar_t* lpwcszWString);
std::wstring UTF8ToWString(const char* lpcszString);
std::string WStringToUTF8(const wchar_t* lpwcszWString);
std::string UTF8ToMBytes(const std::string& str);
std::string MBytesToUTF8(const std::string& str);
