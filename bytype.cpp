#include "bytype.h"
#include <QFileInfo>
#include <QDirIterator>

QVector<QPair<QString, uint64_t>> ByType::calculate(QString const& path)
{

    QDir::Filters filters = QDir::Files | QDir::NoDotAndDotDot  | QDir::Hidden| QDir::NoSymLinks; //необходимые фильтры
    uint64_t allSize = GetFileSize(path, filters);

    QVector<QPair<QString, uint64_t>> result_file;
    QFileInfo file(path);


    if (allSize > 0)
    {
        if (file.isDir())
        {

            QHash<QString, uint64_t> type;  //Хэш-таблица с типами файлов
            QDirIterator Iter(file.absoluteFilePath(), filters, QDirIterator::Subdirectories);

            while (Iter.hasNext())
            {
                Iter.next();
               // auto file = Iter.fileInfo();


                if (type.contains(Iter.fileInfo().suffix()))
                    type[Iter.fileInfo().suffix()] += Iter.fileInfo().size();
                else//иначе создаем запись
                    type[Iter.fileInfo().suffix()] = Iter.fileInfo().size();
            }

            QHashIterator<QString, uint64_t> tableIt(type);
            result_file.resize(type.size());

            for (size_t i = 0; tableIt.hasNext(); ++i)
            {
                tableIt.next();

                if (tableIt.key().isEmpty())
                    result_file[i] = qMakePair(QString("without type"), tableIt.value()); //если нет расширения у файла
                else
                    result_file[i] = qMakePair('.' + tableIt.key(), tableIt.value());
            }
        }
        else
        {
            result_file.append(qMakePair(file.suffix(), file.size()));
        }
    }


    result_file.append(qMakePair(QString("All size"), allSize));//добавляем размер папки
    return result_file;
}
