#include "h_string.h"


size_t wstrlen(const wchar_t* s) {
	const wchar_t* sc;
	for (sc = s; *sc != 0; sc++);
	return sc - s;
}

h_string::h_string() {
	w_str = L"";
	len = 0;
}
h_string::h_string(h_string &s) {
	len = s.len;
	w_str = new wchar_t[len + 1];
	for (int i = 0; i < len; i++)
		w_str[i] = s.w_str[i];
	w_str[len] = 0;
}


h_string::h_string(const wchar_t* s) {
	len = wstrlen(s);
	w_str = new wchar_t[len + 1];
	for (int i = 0; i < len; i++)
		w_str[i] = s[i];
	w_str[len] = 0;
}

h_string::~h_string() {
	if(w_str[0] != 0)
		delete[] w_str;
}

wchar_t* h_string::wc_str() {
	wchar_t* tmp = new wchar_t[len + 1];
	for (int i = 0; i < len; i++)
		tmp[i] = w_str[i];
	return tmp;
}

size_t h_string::length() {
	return len;
}


h_string& h_string::append(h_string& s) {
	wchar_t* tmp = w_str;
	w_str = new wchar_t[len + s.len + 1];
	for (int i = 0; i < len; i++) {
		w_str[i] = tmp[i];
	}
	for (int i = 0; i < s.len; i++) {
		w_str[len + i] = tmp[i];
	}
	w_str[len + s.len] = 0;
	len += s.len;
	delete[] tmp;
	return *this;
}

h_string& h_string::assign(h_string& s) {
	wchar_t* tmp = w_str;
	w_str = new wchar_t[s.len + 1];
	for (int i = 0; i < len; i++) {
		w_str[i] = tmp[i];
	}
	len = s.len;
	w_str[s.len] = 0;
	if (tmp[0] != 0)
	    delete[] tmp;
	return *this;
}


int h_string::find(h_string& s) {
	int length = s.length();
	int check = 0;
	int i = 0;

	for (i = 0; i < len; i++){
		if (check > 0){
			if (w_str[i] != s[check])
				check = 0;
		}

		if (w_str[i] == s[check])
			check++;

		if (check == length)
			break;
	}

	if (check == length)
		return (i - check + 1);
	
	else
		return -1;
}        

h_string h_string::substr(int begin, int len) {
	wchar_t* tmp = new wchar_t[len + 1];
	for (int i = 0; i < len; i++) {
		tmp[i] = w_str[begin + i];
	}
	tmp[len] = 0;
	h_string result(tmp);
	delete[] tmp;
	return result;
}


void h_string::clear() {
	if(w_str[0])
	    delete[] w_str;
	w_str = L"";
	len = 0;
}

h_string h_string::operator+(h_string& s) {
	wchar_t* tmp = new wchar_t[len + s.len + 1];
	for (int i = 0;i < len; i++) {
		tmp[i] = w_str[i];
	}
	for (int i = 0; i < s.len; i++) {
		tmp[len + i] = s[i];
	}
	tmp[len + s.len] = 0;
	h_string result(tmp);
	delete[] tmp;
	return result;
}

h_string h_string::operator+(wchar_t s) {
	wchar_t* tmp = new wchar_t[len + 1 + 1];
	for (int i = 0; i < len; i++) {
		tmp[i] = w_str[i];
	}
	tmp[len] = s;
	tmp[len + 1] = 0;
	h_string result(tmp);
	delete[] tmp;
	return result;
}

h_string& h_string::operator=(h_string& s) {
	len = s.len;
	wchar_t* tmp = w_str;
	w_str = new wchar_t[s.len + 1];
	for (int i = 0; i < len; i++)
		w_str[i] = s.w_str[i];
	w_str[len] = 0;
	if(tmp[0])
	    delete[] tmp;
	return *this;
}

bool h_string::operator==(const h_string& s) {
	if (len == s.len) {
		for (int i = 0; i < len; i++) {
			if (w_str[i] != s.w_str[i])
				return false;
		}
		return true;
	}
	return false;
}

bool h_string::operator>=(const h_string& s) {
	int m_len = len >= s.len ? s.len : len;
	for (int i = 0; i < m_len; i++) {
		if (w_str[i] > s.w_str[i])
			return true;
		else if (w_str[i] < s.w_str[i])
			return false;
	}
	if (len >= s.len)
		return true;
	else
		return false;
}

wchar_t h_string::operator[](int num) {
	const wchar_t result = w_str[num];
	return result;
}