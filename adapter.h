#pragma once

#include "filetablemodel.h"
#include <QtCharts>


class Adapter
{
public:

    virtual ~Adapter() = default;


    virtual void updateData(const QVector<QPair<QString, uint64_t>>& data) = 0;
};


class TableAdapter : public Adapter
{
public:

   TableAdapter(FileTableModel* model);
   void updateData(const QVector<QPair<QString, uint64_t>>& data) override;

private:

   FileTableModel* m_model;
};




class ChartAdapter : public Adapter
{
public:

   ChartAdapter(QChart* chart, QChartView* view);
   virtual ~ChartAdapter();


   void updateData(const QVector<QPair<QString, uint64_t>>& data) override;

protected:

   virtual QAbstractSeries* makeSeries() = 0;
   virtual void appendToSeries(QAbstractSeries* series, const QString& label, float percent) = 0;

   QChart* m_chart;
   QChartView* m_view;
};



class BarChartAdapter : public ChartAdapter
{
public:

   BarChartAdapter(QChartView* view);

private:

   QAbstractSeries* makeSeries() override;
   void appendToSeries(QAbstractSeries* series, const QString& label, float percent) override;
};



class PieChartAdapter : public ChartAdapter
{
public:

   PieChartAdapter(QChartView* view);

private:

   QAbstractSeries* makeSeries() override;
   void appendToSeries(QAbstractSeries* series, const QString& label, float percent) override;
};
