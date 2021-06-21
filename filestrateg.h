#ifndef FILESTRATEG_H
#define FILESTRATEG_H
#pragma once
#include <QString>
#include <QVector>
#include <QTextStream>
#include <QDir>
#include<QDirIterator>


class FileStrateg// Интерфейс всех стратегий
{
public:
    explicit FileStrateg(){}
    virtual ~FileStrateg(){}

    virtual QVector<QPair<QString, uint64_t>> calculate(QString const& path) = 0; // чисто виртуальный метод вычисления, в котором происходт выполнение заданой стратегии
                                                                                   //возращает вектор пар название файла, размер файла в байтах

    uint64_t GetFileSize(QString const& path, QDir::Filters filters) const;// Метод для получения размера сущности в байтах
                                                                            // path - путь к файлу filtrers -  используемые типы файлов


};

#endif // FILESTRATEG_H

