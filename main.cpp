#include "MainWindow_FileBrowser.h"
#include <QApplication>
#include"filestrateg.h"

#include"byfile.h"
#include"bytype.h"
#include<QString>
#include<iostream>
#include <cmath>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow_FileBrowser app;
    app.show();


    return a.exec();
}

