
#include <QWidget>
#include <QFileSystemModel>
#include <filetablemodel.h>
#include <QItemSelection>
#include "filestrateg.h"
#include"observer.h"
namespace Ui
{
    class MainWindow_FileBrowser;
}


class MainWindow_FileBrowser : public QWidget//Класс отвечает за окно внешенего вида приложения
{
    Q_OBJECT

public:


    enum Strategy    //тип выбранной стратегии
    {
        File = 0,
        Type = 1
    };

    MainWindow_FileBrowser(QWidget* parent = nullptr,Strategy strat_type = Strategy::File);

    ~MainWindow_FileBrowser();


public slots:
    //слот изменения стратегии
    void setStrategy(qint32 const& index);
    //слот изменения папки
    void folderChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void updateView(int index);
private:


    QFileSystemModel* m_fileSystem;//модель для работы с файлами

    FileStrateg* m_strategy;//выбраная стратегия

    //FileTableModel* m_tableModel;//указатель на модель отоброженную таблицу

    FilesObserver m_observer;
    QString m_Path;//текущий путь до выбранного файла

    Ui::MainWindow_FileBrowser* ui;//пользовательский интерфейс
};

