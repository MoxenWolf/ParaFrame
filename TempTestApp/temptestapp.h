#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_temptestapp.h"

class TempTestApp : public QMainWindow
{
    Q_OBJECT

public:
    TempTestApp(QWidget *parent = nullptr);
    ~TempTestApp();

private:
    Ui::TempTestAppClass ui;
};
