#ifndef BYFILE_H
#define BYFILE_H
#pragma once
#include<qstring.h>
#include"filestrateg.h"
#include<QDir>
//#include <QtCharts>

#include<QDirIterator>

class ByFile: public  FileStrateg// конкретная стратегия по папкам
{
public:
    explicit  ByFile(){}
    ~ByFile(){}
    QVector<QPair<QString, uint64_t>> calculate(QString const& path );

};

#endif // BYFILE_H

