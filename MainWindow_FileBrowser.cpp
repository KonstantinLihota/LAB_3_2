
#include "MainWindow_FileBrowser.h"
#include "ui_MainWindow_FileBrowse.h"
#include<filetablemodel.h>
#include"byfile.h"
#include"bytype.h"
MainWindow_FileBrowser::MainWindow_FileBrowser(QWidget* parent, MainWindow_FileBrowser::Strategy strat_type) :
    QWidget(parent),
    ui(new Ui::MainWindow_FileBrowser),
    m_fileSystem(new QFileSystemModel(this)),
    m_tableModel(new  FileTableModel(this))
{

    ui->setupUi(this);

    m_fileSystem->setRootPath(QDir::homePath());//устанавливаем начальный  путь

    ui->treeView->setModel(m_fileSystem); //устанавливаем модель

    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);//устанавливаем ратяжение колонок по размеру содержимого

    ui->tableView->setModel(m_tableModel);//устанавливаем модель

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    if (strat_type == Strategy::File)//устанавливаем стратегию
        m_strategy = new ByFile;
    else
        m_strategy = new ByType;

   //механизм сигналы-слоты
    connect(ui->StratComBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow_FileBrowser::setStrategy);

    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow_FileBrowser::folderChanged);
}

MainWindow_FileBrowser::~MainWindow_FileBrowser()
{
    delete ui;
}

void MainWindow_FileBrowser::folderChanged(const QItemSelection& selected, const QItemSelection& /*deselected*/)
{

    m_Path = m_fileSystem->filePath(selected.indexes()[0]);//меняем путь на путь до выбраной папки


    m_tableModel->SetData(m_strategy->calculate(m_Path));//обновление данных

    emit m_tableModel->layoutChanged();
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



     m_tableModel->SetData( m_strategy->calculate(m_Path)); //обновляем данные модели

    emit m_tableModel->layoutChanged();
}
