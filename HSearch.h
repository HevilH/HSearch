#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HSearch.h"

class HSearch : public QMainWindow
{
    Q_OBJECT

public:
    HSearch(QWidget *parent = Q_NULLPTR);

private:
    Ui::HSearchClass ui;
};
