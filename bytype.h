#ifndef BYTYPE_H
#define BYTYPE_H
#pragma once

#include"filestrateg.h"
#include<qstring.h>
#include<QDir>
#include<QDirIterator>

class ByType: public  FileStrateg // конкретная стратегия по типоам файлов
{
public:
    explicit ByType(){}
    ~ByType(){}
    QVector<QPair<QString, uint64_t>> calculate(QString const& path);

};

#endif // BYTYPE_H
