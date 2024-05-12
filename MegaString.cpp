#include "MegaString.h"
#include <string.h>
#include <iostream>

MegaString::MegaString() : mStr(nullptr), mLen(0) 
{

}

MegaString::MegaString(const char* str) : mStr(nullptr), mLen(0)
{
	if ((nullptr == str) || ('\0' == str[0])) {
		return;
	}

	size_t len = strlen(str) + 1;

	mStr = (unsigned char*)new char[len];

	if (nullptr == mStr){
		return;
	}

	strncpy_s((char*)mStr, len, str, strlen(str));
	//mStr[len] = '\0';
}

MegaString::~MegaString(){
	if (nullptr != mStr) {
		delete[] mStr;
	}

	mLen = 0;
}

bool MegaString::empty() const
{
	return ((nullptr == mStr) || (0 == mLen));
}

MegaString& MegaString::operator=(const char* str)
{
	if ((char*)mStr == str) {
		return *this;
	}

	//If its not same, then do the copy
	if ((nullptr == str) || ('\0' == str[0]))
	{
		return *this;
	}

	if (nullptr != mStr)
	{
		delete[] mStr;
	}

	//mStr = nullptr;
	mLen = 0;

	size_t len = strlen(str) + 1;

	mStr = (unsigned char*)new char[len];

	if (nullptr == mStr) {
		return *this;
	}

	mLen = strlen(str);

	strncpy_s((char*)mStr, len, str, strlen(str));
	//mStr[mLen] = '\0';

	return *this;
}

MegaString& MegaString::operator=(const MegaString& str)
{
	if (this == &str) {
		return *this;
	}

	//If its not same, then do the copy
	if (str.empty())
	{
		reset();
		return *this;
	}

	if (nullptr != mStr) {
		delete[] mStr;
	}

	//mStr = nullptr;
	mLen = 0;

	mStr = (unsigned char*)new char[str.mLen + 1];

	if (nullptr == mStr) {
		return *this;
	}

	mLen = str.mLen;
	strncpy_s((char*)mStr, (str.mLen+1), (char*)str.mStr, str.mLen);

	return *this;
}


void MegaString::reset() {
	if (mStr) {
		delete[] mStr;
	}

	//mStr = nullptr;
	mLen = 0;
}

const char* MegaString::data() const
{
	return (char*)mStr;
}

unsigned int MegaString::length() const
{
	return unsigned int(mLen);
}

void MegaString::clear()
{
	if (mStr) {
		delete[] mStr;
	}

	//mStr = nullptr;
	mStr = (unsigned char*)new char[1];

	mLen = 1;
	mStr[0] = '\0';
}

//This function replaces the string from the position mention to the end of the string
MegaString& MegaString::replace(size_t pos, size_t len, const MegaString& str)
{
	//If replace length is greater than actual length or position is beyong mLen, discard
	if (pos > mLen){
		return *this;
	}

	size_t newLen = mLen - len + str.mLen;
	size_t oldLen = mLen - len - pos ;

	//Store the existing data to temp string
	unsigned char* tempStr = (unsigned char*)new char[mLen+1];
	strncpy_s((char*)tempStr, mLen+1, (const char*)mStr, mLen);

	reset();

	mLen = newLen;
	mStr = (unsigned char*)new char[newLen + 1];
	strncpy_s((char*)mStr, pos + 1, (const char*)tempStr, pos);
	strncpy_s((char*)(mStr + pos), str.mLen+1, (const char*)str.mStr, str.mLen);
	strncpy_s((char*)(mStr + pos+ str.mLen), oldLen + 1, (const char*)(tempStr + pos + len), oldLen);
	mStr[mLen] = '\0';

	delete[] tempStr;

	return *this;
}

//This function appends a data to the end of the string
MegaString& MegaString::append(const MegaString& str)
{
	size_t oldLen = mLen;
	size_t newLen = mLen + str.mLen;

	//Store the existing data to temp string
	unsigned char * tempStr = (unsigned char*)new char[mLen+1];
	strncpy_s((char*)tempStr, mLen+1, (char*)mStr, mLen);

	reset();

	mLen = newLen;
	mStr = (unsigned char*)new char[newLen + 1];
	strncpy_s((char*)mStr, oldLen+1, (char*)tempStr, oldLen);
	strncpy_s((char*)(mStr+oldLen), str.mLen+1, (char*)str.mStr, str.mLen);
	mStr[mLen] = '\0';

	delete[] tempStr;

	return *this;
}

//This function removes the last character of the string
void MegaString::pop_back() 
{
	if (empty())
	{
		return;
	}

	mStr[mLen-1] = '\0';
	mLen = mLen - 1;

}

//This function adds a charcater to the end of the string
void MegaString::push_back(char c)
{
	//Copy the data to temp char pointer
	size_t oldLen = mLen;
	unsigned char* tempStr = (unsigned char*)new char[mLen+1];
	strncpy_s((char*)tempStr, mLen+1, (char*)mStr, mLen);
	tempStr[mLen] = '\0';

	reset();

	mLen = oldLen + 1;
	mStr = (unsigned char*)new char[mLen + 1];
	strncpy_s((char*)mStr, oldLen+1, (char*)tempStr, oldLen);
	strncat_s((char*)(mStr+oldLen), 2, (char*)&c, 1);
	mStr[mLen] = '\0';
}

//This function will generate a substring based on the data position
MegaString MegaString::substr(size_t pos, size_t len) const
{

	//Return null data for now
	if (len == 0 || pos == mLen) {
		return MegaString("");
	}

	//If length is configured greater than mas string size, copy only till maxlength of existing string
	if (len > mLen-pos)
	{
		len = mLen - pos;
	}

	unsigned char* tempStr = (unsigned char*)new char[len + 1];
	strncpy_s((char*)tempStr, len+1, (char*)mStr+pos, len);
	tempStr[len] = '\0';

	MegaString newStr((const char*)tempStr);
	
	delete[] tempStr;
	return newStr;
}