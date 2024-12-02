#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChart>
#include <QLayout>
#include <QKeyEvent>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QLayoutItem>

using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QChartView *chartViewA_1 = new QChartView();
    QChartView *chartViewA_2 = new QChartView();
    QChartView *chartViewB_1 = new QChartView();
    QChartView *chartViewB_2 = new QChartView();


    QLineSeries *seriesDirectA = new QLineSeries();
    QLineSeries *seriesReverseA = new QLineSeries();
    QLineSeries *seriesStepA = new QLineSeries();
    QLineSeries *seriesRandomA = new QLineSeries();

    QLineSeries *seriesDirectB = new QLineSeries();
    QLineSeries *seriesReverseB = new QLineSeries();
    QLineSeries *seriesStepB = new QLineSeries();
    QLineSeries *seriesRandomB = new QLineSeries();



protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    Ui::MainWindow *ui;
    void series_init(){
        seriesDirectA->setName("direct");
        seriesReverseA->setName("reverse");
        seriesStepA->setName("step");
        seriesRandomA->setName("random");
        seriesDirectB->setName("direct");
        seriesReverseB->setName("reverse");
        seriesStepB->setName("step");
        seriesRandomB->setName("random");
    }
    void clearLayout(QLayout *layout, bool deleteWidgets = true)
    {
        while (QLayoutItem* item = layout->takeAt(0))
        {
            if (deleteWidgets)
            {
                if (QWidget* widget = item->widget())
                    widget->deleteLater();
            }
            if (QLayout* childLayout = item->layout())
                clearLayout(childLayout, deleteWidgets);
            delete item;
        }
    }

};
#endif // MAINWINDOW_H
