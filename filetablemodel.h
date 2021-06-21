
#pragma once
#include <QAbstractTableModel>



class FileTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    FileTableModel(QObject* parent = nullptr,
    QVector<QPair<QString, uint64_t>> const& filesData = QVector<QPair<QString, uint64_t>>());


    void SetData(QVector<QPair<QString, uint64_t>> const& filesData);//обновление данных модели
    QVector<QPair<QString, uint64_t>> const& getData(); //метод возращает данные модели


    int rowCount(const QModelIndex& parent = QModelIndex()) const override; //строкив таблице

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;//столбцы

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;//имена колонок

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;//представление данных

private:

    QVector<QPair<QString, uint64_t>> m_filesData;//данные модели
};



