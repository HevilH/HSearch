#pragma once

#include <wchar.h>

class h_string{

private:
	int len;
public:
	wchar_t* w_str;
	h_string();
	h_string(h_string &s);
	h_string(const wchar_t* s);
	~h_string();
	wchar_t* wc_str();         //wchar_t 반환
	size_t length();                 //길이 반환
	h_string& append(h_string& s);   //문자열 확장
	h_string& assign(h_string& s);   //문자열 복사
	int find(h_string& s);           //KMP
	h_string substr(int begin, int len);    //서브 스트링 반환
	void clear();                    //초기화

	//연산자 오버로딩
	h_string operator+(h_string& s);
	h_string operator+(wchar_t s);
	h_string& operator=(h_string& s);
	bool operator==(const h_string& s);
	bool operator>=(const h_string& s);
	wchar_t operator[](int num);
};

size_t wstrlen(const wchar_t *s);

