#pragma once

#include <string>
#include <list>
#include <source_location>
#include <iostream>

/*Core*/
#include <QtCore/QObject>
#include <QtWidgets/QApplication>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QStringList>
#include <QtCore/QSize>
#include <QCloseEvent>
#include <QtGui/QPalette>
#include <QtGui/QColor>
#include <QtCore/QRandomGenerator>

#include <QFileInfo>
#include <QLibrary>

/*Widgets*/
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

/*Layouts*/
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>

/*Events*/
/*Local*/
#include "paralib.h"

struct ParaBrowserSettings
{
    QSize lastKnownSize{-1, -1};
};

//typedef void (*protoDoEmpty)();
//typedef void (*protoDoInt)(int);
//typedef int (*protoIncInt)(int);
//typedef void (*protoDoString)(std::string);
//typedef std::string (*protoRetString)(std::string);

typedef int (*protoPluginEnable)();
typedef int (*protoPluginDisable)();
typedef std::list<std::string>(*protoPluginGetInterfaceVersion)();

class ParaBrowser : public QMainWindow
{
    Q_OBJECT

public:
    ParaBrowser(QWidget *parent = Q_NULLPTR);
    ParaBrowser(ParaBrowserSettings& settings, QWidget* parent = Q_NULLPTR);
    ~ParaBrowser();

    const ParaBrowserSettings getSettings();
protected:
    void closeEvent(QCloseEvent*) override;
private:
    void uiCreate();
    void conSS();

    QLabel* lblStatusReturn;

    ParaBrowserSettings m_settings;
    QFont fontInfo{ "consolas", 8};
    QFont fontInteract{ "consolas", 10 };
    int topPanelStyle{ QFrame::Panel/* | QFrame::Sunken */};

    QLibrary* libEventHorizon;
    protoPluginEnable pluginEnable = Q_NULLPTR;
    protoPluginDisable pluginDisable = Q_NULLPTR;
    protoPluginGetInterfaceVersion getInterfaceVersion = Q_NULLPTR;


    /*protoDoEmpty ehDoEmpty = Q_NULLPTR;
    protoDoInt ehDoInt;
    protoIncInt ehIncInt = Q_NULLPTR;
    protoDoString ehDoString;
    protoRetString ehRetString;*/
private slots:
    void slot_connect(bool);
};