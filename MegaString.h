#pragma once

#ifndef _MegaString_H
#define _MegaString_H

class MegaString
{
public:
	MegaString();
	MegaString(const char* str);
	~MegaString();
	MegaString& operator=(const char* str);
	MegaString& operator=(const MegaString& str);

	const char* data() const;
	unsigned int length() const;
	bool empty() const;
	void clear();
	void reset();

	MegaString& replace(size_t pos, size_t len, const MegaString& str);
	MegaString& append(const MegaString& str);
	void pop_back();
	void push_back(char c);
	MegaString substr(size_t pos = 0, size_t len = -1) const;
private:
	unsigned char* mStr = nullptr;
	size_t mLen = 0;

};

#endif