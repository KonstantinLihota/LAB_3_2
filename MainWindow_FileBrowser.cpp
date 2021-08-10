
#include "MainWindow_FileBrowser.h"
#include "ui_MainWindow_FileBrowse.h"
#include<filetablemodel.h>
#include"byfile.h"
#include"bytype.h"
MainWindow_FileBrowser::MainWindow_FileBrowser(QWidget* parent, MainWindow_FileBrowser::Strategy strat_type) :
    QWidget(parent),
    ui(new Ui::MainWindow_FileBrowser),
    m_fileSystem(new QFileSystemModel(this))
   // m_tableModel(new  FileTableModel(this))
{

    ui->setupUi(this);

    m_fileSystem->setRootPath(QDir::homePath());//устанавливаем начальный  путь

    ui->treeView->setModel(m_fileSystem); //устанавливаем модель

    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);//устанавливаем ратяжение колонок по размеру содержимого

    //ui->tableView->setModel(m_tableModel);//устанавливаем модель

    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    FileTableModel* model = new FileTableModel(this);
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //подписываем на оповещения
    m_observer.subscribe(new TableAdapter(model));
    m_observer.subscribe(new BarChartAdapter(ui->chartView));
    m_observer.subscribe(new PieChartAdapter(ui->chartView));

    if (strat_type == Strategy::File)//устанавливаем стратегию
        m_strategy = new ByFile;
    else
        m_strategy = new ByType;

   //механизм сигналы-слоты
    connect(ui->StratComBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow_FileBrowser::setStrategy);

    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow_FileBrowser::folderChanged);
    connect(ui->displayComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow_FileBrowser::updateView);
}

MainWindow_FileBrowser::~MainWindow_FileBrowser()
{
    delete ui;
    delete m_strategy;

    for(int i = 0; i < m_observer.count(); ++i)
        delete m_observer.getByIndex(i);
}
void MainWindow_FileBrowser::updateView(int index)
{
    //обновляем контретного подписчки, потому что если выбрана диаграмма для отображения данных
    //то оповещение всех диаграмм приведет к тому, что каждая диаграмма будет
    //перекрывать предыдущую и в итоге отобразиться та диаграмма, которая была оповещена последней
    m_observer.updateByIndex(m_strategy->calculate(m_Path), index);
    ui->stackedWidget->setCurrentIndex(index == 0 ? 0 : 1);
}
void MainWindow_FileBrowser::folderChanged(const QItemSelection& selected, const QItemSelection& /*deselected*/)
{

    m_Path = m_fileSystem->filePath(selected.indexes()[0]);//меняем путь на путь до выбраной папки




    auto data = m_strategy->calculate(m_Path);
    m_observer.updateByIndex(data, ui->displayComboBox->currentIndex());
}

void MainWindow_FileBrowser:: setStrategy(qint32 const& index)//метод для устанавки стратегии
{
    delete m_strategy;


    switch (index)
    {
    case 0:
        m_strategy = new ByFile();
        break;
    case 1:
        m_strategy = new ByType();
        break;
    }



    //если папка не выбрана, то выходим
    if (m_Path.isEmpty())
        return;

    //обновляем данные модели
    auto data = m_strategy->calculate(m_Path);
    m_observer.updateByIndex(data, ui->displayComboBox->currentIndex());
}
