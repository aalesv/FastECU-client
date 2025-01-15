// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    bool debug_console = false;

    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "debug"))
            debug_console = true;
    }

#ifdef _WIN32
    if (!debug_console)
    {
        if (AttachConsole(ATTACH_PARENT_PROCESS)) {
            freopen("CONOUT$", "w", stdout);
            freopen("CONOUT$", "w", stderr);
        }
    }
    else
    {
        if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
            freopen("CONOUT$", "w", stdout);
            freopen("CONOUT$", "w", stderr);
        }
    }
#endif

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QObject::connect(&a, &QCoreApplication::aboutToQuit,
                     &w, &MainWindow::aboutToQuit);

    return a.exec();
}
