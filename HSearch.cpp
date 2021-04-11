#include "HSearch.h"

HSearch::HSearch(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
	//std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    dict = new h_trie;
    init_dict();
	htmls = new article[HTML_NUM];
	extract_info();
	index_table = new h_unordered_map;
	build_index();
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(search_html()));
	h_string gumsak = L"ÌåÓý";
	std::vector < std::pair<int,int> > result = index_table->search(gumsak);
	int a = 1;
	//std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	//std::chrono::duration<double> sec = end - start;
	//ui.label->setText(QString::number(sec.count()));
}


void HSearch::init_dict() {
	std::locale loc("chs");
	std::wcout.imbue(loc);
	std::wifstream input_dict(L"´Ê¿â.dic", std::ios::binary);
	std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header>;
	if (input_dict.is_open()) {
		input_dict.imbue(std::locale(input_dict.getloc(), codecvtToUnicode));
		std::wstring wline;
		while (std::getline(input_dict, wline)) {
			h_string temp(wline.data());
			dict->insert(temp);
		}
	}
	return;
}

void HSearch::extract_info() {
	int result = 0;
	struct _finddata_t c_file;
	intptr_t hFile = _findfirst("input/*.html", &c_file);
	if (hFile == -1) return;
	for(int i = 0; i < HTML_NUM; i++){
		std::string file_addr = "input/";
		file_addr += c_file.name;
		htmls[i].parse_html(file_addr, i);
		result = _findnext(hFile, &c_file);
	} 
	_findclose(hFile);
	return;
}

void HSearch::divide_word(h_string &str, h_list* result) {
	int len = str.length();
	int index = 0;
	while (index < len) {
		int check = dict->search(str, index);
		if (check > 0) {
			result->push_back(str.substr(index, check));
			index += check;
		}
		else {
			index += 1;
		}
	}
}

void  HSearch::build_index() {
	for (int i = 0; i < HTML_NUM; i++) {
		h_list* result = new h_list;
		divide_word(htmls[i].get_title(), result);
		divide_word(htmls[i].get_question(), result);
		divide_word(htmls[i].get_author(), result);
		divide_word(htmls[i].get_content(), result);
		h_string temp = result->pop_back();
		while (temp.length() != 0) {
			index_table->insert(temp, i + 1, htmls[i]);
			temp = result->pop_back();
		}
	}
}

void  HSearch::search_html() {
	QString input = ui.textEdit->toPlainText();
	wchar_t* w_input = new wchar_t[input.length() + 1];
	input.toWCharArray(w_input);
	w_input[input.length()] = 0;
	h_string m_input(w_input);
	h_list *result = new h_list;
	divide_word(m_input, result);
	std::vector<std::vector<double>> result_v;
	int len = result->size();
	m_input = result->pop_front();
	int i = 1;
	bool check = false;
	while (m_input.length() != 0) {
		std::vector<std::pair<int,int>> result_t = index_table->search(m_input);
		for (int j = 0; j < result_t.size(); j++) {
			for (int k = 0; k < result_v.size(); k++) {
				if (result_v[k][0] == result_t[j].first) {
					check = true;
					double tf = (double)result_t[j].second / (double)htmls[(result_t[j].first - 1)].get_tf();
					double idf = log10((double)520 / (double)index_table->get_df(m_input));
					result_v[k][i] = tf * idf;
					break;
				}
			}
			if (check == false) {
				std::vector<double> temp(len + 1);
				temp[0] = (double)result_t[j].first;
				double tf = (double)result_t[j].second / (double)htmls[(result_t[j].first - 1)].get_tf();
				double idf = log10((double)520 / (double)index_table->get_df(m_input));
				temp[i] = tf * idf;
				result_v.push_back(temp);
			}
			check = false;
		}
		i++;
		m_input = result->pop_back();
	}
	std::vector<std::pair<double, int>> fin_result;
	for (int k = 0; k < result_v.size(); k++) {
		std::pair<double, int> tp;
		tp.second = result_v[k][0];
		double temp_w = 0;
		for (i = 1; i < result_v[k].size(); i++)
			temp_w += pow(result_v[k][i], 2);
		tp.first = temp_w;
		fin_result.push_back(tp);
	}
	sort(fin_result.begin(), fin_result.end(), std::greater<>());
	QString m_html;
	for (int i = 0; i < fin_result.size(); i++) {
		m_html = m_html + QString::number(fin_result[i].second) + "\n";
	}
	ui.plainTextEdit->setPlainText(m_html);
}