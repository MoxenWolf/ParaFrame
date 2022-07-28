#include "parabrowser.h"

/*Core*/
#include <QtWidgets/QApplication>
#include <QtGui/QIcon>
#include <QtGui/QFont>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QSettings>
#include <QtCore/QSize>

/*Widgets*/
/*Layouts*/
/*Events*/
/*Local*/


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationVersion(PARAFRAME_VERSION);
    app.setWindowIcon(QIcon(":/Images/logo_ico"));
    app.setFont(QFont("Consolas"));

    //Parse Commandline
    QCommandLineParser parser;
    parser.setApplicationDescription("ParaFrame Browser");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption devAccess(QStringList() << "d" << "developer" << "Activate Developer Access Mode");
    parser.addOption(devAccess);

    QCommandLineOption resetSettings(QStringList() << "r" << "reset" << "Reset Settings");
    parser.addOption(resetSettings);

    parser.process(app);

    //Restore User Settings
    ParaBrowserSettings settings;

    QSettings appUserSettings(QSettings::Scope::UserScope, "ParanoidFramework", "ParaBrowser", &app);
    if (!parser.isSet(resetSettings))
    {
        appUserSettings.beginGroup("General");
        appUserSettings.beginGroup("LastKnownDimensions");

        settings.lastKnownSize = QSize(appUserSettings.value("width", -1).toInt(),
            appUserSettings.value("height", -1).toInt());

        appUserSettings.endGroup();
        appUserSettings.endGroup();
    }

    ParaBrowser w(settings);
    w.show();

    int rtnCode = app.exec();
    
    //Save User Settings
    settings = w.getSettings();

    appUserSettings.beginGroup("General");
    appUserSettings.beginGroup("LastKnownDimensions");

    appUserSettings.setValue("width", settings.lastKnownSize.width());
    appUserSettings.setValue("height", settings.lastKnownSize.height());

    appUserSettings.endGroup();
    appUserSettings.endGroup();

    return rtnCode;
}
