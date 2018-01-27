#include "mainwindow.h"

#include <QCoreApplication>
#include <QApplication>
#include <QCommandLineParser>

#include <KAboutData>
#include <KLocalizedString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KLocalizedString::setApplicationDomain("fusemount");

    KAboutData aboutData(
                            // The program name used internally. (componentName)
                            QStringLiteral("fusemount"),
                            // A displayable program name string. (displayName)
                            i18n("FuseMount"),
                            // The program version string. (version)
                            QStringLiteral("0.1a"),
                            // Short description of what the app does. (shortDescription)
                            i18n("GUI frontend for sshfs."),
                            // The license this code is released under
                            KAboutLicense::GPL,
                            // Copyright Statement (copyrightStatement = QString())
                            i18n("(c) 2018"),
                            // Optional text shown in the About box.
                            // Can contain any information desired. (otherText)
                            i18n("Frontend for sshfs allowing grouped mounts and using KWallet."),
                            // The program homepage string. (homePageAddress = QString())
                            QStringLiteral("https://github.com/Oinosseus/FuseMount"),
                            // The bug report email address
                            // (bugsEmailAddress = QLatin1String("submit@bugs.kde.org")
                            QStringLiteral(""));
    aboutData.addAuthor(i18n("Thomas Weinhold"), i18n(""), QStringLiteral("Thomas.Weinhold@stratoinos.de"), QStringLiteral(""), QStringLiteral(""));
    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    aboutData.setupCommandLine(&parser);
    parser.process(a);
    aboutData.processCommandLine(&parser);

    if (a.isSessionRestored()) {
        kRestoreMainWindows<MainWindow>();
    } else {
        MainWindow *w = new MainWindow();
        w->setObjectName("mainwindow");
        w->show();
    }
    

    return a.exec();
}
