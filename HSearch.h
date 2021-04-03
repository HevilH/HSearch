#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HSearch.h"

#include "h_set.h"
#include "h_unordered_map.h"
#include "h_list.h"
#include "h_stack.h"
#include "h_string.h"


#include "h_search.h"

class HSearch : public QMainWindow
{
    Q_OBJECT

public:
    HSearch(QWidget *parent = Q_NULLPTR);

private:
    Ui::HSearchClass ui;
};
