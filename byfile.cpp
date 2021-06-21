
#include"byfile.h"
#include <QFileInfo>
#include <QDirIterator>
QVector<QPair<QString, uint64_t>> ByFile::calculate(QString const& path)// функция подсчета для стратегии по папкам
{

    QDir::Filters filters = QDir::Files | QDir::Dirs | QDir::NoSymLinks | QDir::Hidden| QDir::NoDotAndDotDot ; // используемые группы файлов

    QVector<QPair<QString, uint64_t>> result_file;

    uint64_t allSize = GetFileSize(path, filters);
    QFileInfo file(path);


    if (allSize > 0)//Если папка не пустая
    {
        if (file.isDir())//для папок
        {

            QDirIterator Iter(file.absoluteFilePath(), filters);// итератор по папкам

            while (Iter.hasNext())
                       {
                            Iter.next();
                            uint64_t size;
                            if (Iter.fileInfo().isDir()){
                           size = GetFileSize( Iter.fileInfo().absoluteFilePath(), filters);//вычисляем размер папки
                            }
                            else{
                                size = Iter.fileInfo().size();//если это не папка вычисляем размер файла
                            }

                           result_file.append(qMakePair(Iter.fileInfo().fileName(),size)); //добавляем в итоговый вектор
                       }
        }
        else//для файлов
        {
            result_file.append(qMakePair(file.fileName(), (uint64_t)file.size()));
        }
    }


    result_file.append(qMakePair(QString("All size"), allSize));
    return result_file;
}

