#ifndef SHOWPICTURE_H
#define SHOWPICTURE_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QDialog>
#include<QVBoxLayout>

class ShowPicture:public QDialog
{
 Q_OBJECT
public:
    ShowPicture();

};

#endif // SHOWPICTURE_H
