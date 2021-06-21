#include"filestrateg.h"
#include<QDir>
#include<QDirIterator>
uint64_t FileStrateg::GetFileSize (QString const& path, QDir::Filters filters) const
{
    QFileInfo file(path);
    if (file.dir().isEmpty()) //если папки пустая
        return 0;

    if (file.isDir())
    {

        QDirIterator Iter(file.absoluteFilePath(), filters, QDirIterator::Subdirectories);
        uint64_t sum = 0;

        while (Iter.hasNext())
        {
            Iter.next();
            sum += Iter.fileInfo().size();//накапливаем общий размер папки
        }

        return sum;
    }
    else
        return file.size();
}

