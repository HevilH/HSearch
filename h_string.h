#pragma once
#include <wchar.h>
class h_string{

private:
	wchar_t *w_str;
	int len;
public:
	h_string();
	h_string(h_string &s);
	h_string(wchar_t* s);
	~h_string();
	wchar_t* wc_str();         //wchar_t 반환
	size_t length();                 //길이 반환
	h_string& append(h_string& s);   //문자열 확장
	h_string& assign(h_string& s);   //문자열 복사
	int find(h_string& s);           //KMP
	h_string substr(int begin, int len);    //서브 스트링 반환, KMP
	void clear();                    //초기화

	//연산자 오버로딩
	h_string operator+(const h_string& s);
	h_string& operator=(h_string& s);
	bool operator==(const h_string& s);
	bool operator>=(const h_string& s);

	/*h_string& append(wchar_t* s);
	h_string& assign(wchar_t* s);
	int find(wchar_t* s);
	h_string operator+(wchar_t* s);
	h_string operator=(wchar_t* s);
	bool operator==(wchar_t* s);*/

};

size_t wstrlen(wchar_t *s);

