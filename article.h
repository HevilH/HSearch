#pragma once
#include "h_stack.h"
#include <string>
#include <fstream>
#include <locale> 
#include <codecvt>
#include <iostream>

#define HTML_NUM 520

class article
{
private:
	int ID;
	h_string title;
	h_string question;
	h_string author;
	h_string content;
	int m_tf;
public:
	article() {
		ID = 0;
		m_tf = 0;
	}
	void parse_html(std::string file_name, int id) {
		std::locale loc("chs");
		std::wcout.imbue(loc);
		ID = id;
		std::wifstream input_html;
		std::wstring wline;
		input_html.open(file_name, std::ios::binary);
		std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header>;
		if (input_html.is_open()) {
			input_html.imbue(std::locale(input_html.getloc(), codecvtToUnicode));
			h_stack m_stack;
			h_string data_str;
			h_string tag_str;
			h_string question_tag(L"h2 class=\"question-title\"");
			h_string author_tag(L"span class=\"author\"");
			h_string content_tag(L"div class=\"content\"");
			bool is_open = false;
			bool is_end = false;
			bool is_check = false;
			while (std::getline(input_html, wline)) {
				h_string input_str(wline.data());
				for (int i = 0; i < input_str.length(); i++) {
					if (input_str[i] == '/' && input_str[i - 1] == '<') {
						is_end = true;
						tag_str = tag_str + input_str[i];
					}
					else if (input_str[i] == '>' && is_open == true) {
						is_open = false;
						tag_str = tag_str + input_str[i];
						if (is_end == false) {
							m_stack.push(tag_str);
							if (tag_str == L"<title>" || tag_str.find(question_tag) != -1 || tag_str.find(author_tag) != -1 || tag_str.find(content_tag) != -1)
								is_check = true;
							if (tag_str.find(question_tag) != -1)
								int c = 12;
						}
						else {
							h_string tag = m_stack.pop();
							if (tag == L"<title>") {
								title = data_str;
								data_str.clear();
								is_check = false;
							}
							else if (tag.find(question_tag) != -1) {
								question = question + data_str;
								data_str.clear();
								is_check = false;
							}
							else if (tag.find(author_tag) != -1) {
								author = author + data_str;
								data_str.clear();
								is_check = false;
							}
							else if (tag.find(content_tag) != -1) {
								content = content + data_str;
								data_str.clear();
								is_check = false;
							}
						}
						is_end = false;
						tag_str.clear();
					}
					else if (input_str[i] == '<' || is_open == true) {
						is_open = true;
						tag_str = tag_str + input_str[i];
					}
					else if (is_check == true) {
						data_str = data_str + input_str[i];
					}
				}

			}
			int a = 2;
		}

	}
	int get_tf() {
		return m_tf;
	}
	void set_tf(int n) {
		m_tf = n;
	}
	h_string& get_title() {
		return title;
	}
	h_string& get_author() {
		return author;
	}
	h_string& get_content() {
		return content;
	}
	h_string& get_question() {
		return question;
	}

};

