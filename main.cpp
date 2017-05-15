#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    if (QCoreApplication::arguments().contains(QStringLiteral("--multisample")))
        fmt.setSamples(4);
    if (QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"))) {
        fmt.setVersion(3, 2);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    }
    QSurfaceFormat::setDefaultFormat(fmt);

    MainWindow mainWindow;
    if (QCoreApplication::arguments().contains(QStringLiteral("--transparent"))) {
        mainWindow.setAttribute(Qt::WA_TranslucentBackground);
        mainWindow.setAttribute(Qt::WA_NoSystemBackground, false);
    }
    mainWindow.resize(mainWindow.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = mainWindow.width() * mainWindow.height();
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        mainWindow.show();
    else
        mainWindow.showMaximized();
    return app.exec();
}
/*
#include "mainwindow.h"
#include <QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3,3);

    Window window;
    window.setFormat(format);
    window.resize(QSize(800,600));
    window.show();

    return a.exec();
}*/
