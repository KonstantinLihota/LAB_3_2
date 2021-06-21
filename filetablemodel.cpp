#include "filetablemodel.h"
#include <QLocale>
#include <algorithm>

FileTableModel::FileTableModel(QObject* init , QVector<QPair<QString, uint64_t>> const& Data) :
    QAbstractTableModel(init),
    m_filesData(Data)
{}


void FileTableModel::SetData(QVector<QPair<QString, uint64_t>> const& Data)
{
    m_filesData = Data;
}

QVector<QPair<QString, uint64_t>>const& FileTableModel::getData()
{
    return m_filesData;
}

int FileTableModel::rowCount(const QModelIndex&) const
{
    return m_filesData.size();
}

int FileTableModel::columnCount(const QModelIndex&) const
{
    return 3;
}

QVariant FileTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal&&role == Qt::DisplayRole )
    {
        switch (section)
        {

        case 0:
            return QString("Name");

        case 1:
            return QString("Size");

        case 2:
            return QString("%");
        }
    }

    return QVariant();
}

QVariant FileTableModel::data(const QModelIndex& index, int role) const
{

   if (role == Qt::DisplayRole)
   {
        switch (index.column())
        {

        case 0://для 1 столбца
            return QString(m_filesData[index.row()].first); //возвращаем название сущности

        case 1://для 2 столбца

            return QLocale(QLocale::English).formattedDataSize(m_filesData[index.row()].second);//возращает размер

        case 2://для 3 столбца


            double totalSize = m_filesData[m_filesData.size() - 1].second;//процентное соотношение
            double percent = double(m_filesData[index.row()].second) / totalSize * 100;

            if(totalSize > 0){//для не пустойдиректории
                if (percent >= 1 ){
                    return QString::number(percent, 'f', 2);
                }
                else{
            {
                return ("<1");//для файла или директории меньше процента
                    }
            }
            }
            else{
                return 0;
            }



            return QString();
        }
    }

    return QVariant();
}

