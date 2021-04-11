#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HSearch.h"
#include "h_string.h"
#include "h_set.h"
#include "h_list.h"
#include "h_trie.h"
#include "h_unordered_map.h"
#include "h_stack.h"
#include <io.h>
#include <Windows.h>
#include <chrono>
#include <algorithm>


#define HTML_NUM 520
class HSearch : public QMainWindow
{
    Q_OBJECT

public:
    HSearch(QWidget *parent = Q_NULLPTR);
    void init_dict();
    void extract_info();
    void divide_word(h_string &str, h_list *result);
    void build_index();
public slots:
    void search_html();
private:
    Ui::HSearchClass ui;
    h_trie* dict;
    article* htmls;
    h_unordered_map* index_table;
};
