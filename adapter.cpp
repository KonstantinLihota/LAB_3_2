#include "adapter.h"
#include<iostream>
TableAdapter::TableAdapter(FileTableModel* model) :
   m_model(model)
{}

void TableAdapter::updateData(const QVector<QPair<QString, uint64_t>>&data)
{

   if(m_model)//когда есть указатель на модель передаем в нее данные
   {
      m_model->SetData(data);
   }
}

ChartAdapter::ChartAdapter(QChart* chart, QChartView* view) :
   m_chart(chart),
   m_view(view)
{}

ChartAdapter::~ChartAdapter()
{
   delete m_chart;
}


void ChartAdapter::updateData(const QVector<QPair<QString, uint64_t>>& data)//обновление данных в диаграмме
{
    m_chart->removeAllSeries();

    if(m_view)
    {
        if (!data.empty())
        {
           QAbstractSeries* series = makeSeries();

           float other_percent = 0.0;//здесь накапливаем процент файлов которые занимают мало место(меньше 3 процентов)

           QString label;

           float percent = 0;

           float totalSize = 0.;
           for (int i=0; i<data.size(); i++){//вычисляем общую длинну
                totalSize +=  data[i].second;
           }
           if (totalSize > 0)
           {
              for (int i = 0;  i < data.size() ; ++i)//вычисляем процент для каждого файла
              {  percent = float(data[i].second) / totalSize * 100;
                 if (percent >3.)
                 {
                    label = data[i].first + " - " + QString::number(percent, 'g', 3) + "%";
                    appendToSeries(series, label, percent);//добовляем в серию
                 }
                 else
                 {
                    other_percent+=percent;//прибовляем к others file
                 }



              }

              label = "others - " + QString::number(other_percent, 'g', 3) + "%";
              appendToSeries(series, label, other_percent);

              m_chart->addSeries(series);//передаем серию
              m_chart->setTheme(QChart::ChartTheme::ChartThemeLight);//
              m_chart->legend()->setAlignment(Qt::AlignRight);//устанавливаем легенду справа
           }
           else{//если файл пуст графики отображаются пустыми с пометко 'empty'
               appendToSeries(series, "empty", 0);
               m_chart->addSeries(series);
               m_chart->setTheme(QChart::ChartTheme::ChartThemeQt);
               m_chart->legend()->setAlignment(Qt::AlignRight);
           }
           m_view->setChart(m_chart);
        }
    }
}

BarChartAdapter::BarChartAdapter(QChartView* view) :
   ChartAdapter(new QChart, view)
{}

QAbstractSeries* BarChartAdapter::makeSeries()
{
   return new QBarSeries();
}

void BarChartAdapter::appendToSeries(QAbstractSeries* series, const QString& label, float percent)
{
   QBarSet* set = new QBarSet(label);
   set->append(percent);
   static_cast<QBarSeries*>(series)->append(set);
}

PieChartAdapter::PieChartAdapter(QChartView* view) :
   ChartAdapter(new QChart, view)
{}

QAbstractSeries* PieChartAdapter::makeSeries()
{
   return new QPieSeries();
}

void PieChartAdapter::appendToSeries(QAbstractSeries* series, const QString& label, float percent)
{
   QPieSlice* slice = new QPieSlice(label, percent);
   slice->setValue(percent);
   static_cast<QPieSeries*>(series)->append(slice);
}
