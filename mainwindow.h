#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChart>
#include <QKeyEvent>
#include <QChart>
#include <QChartView>
#include <QLineSeries>

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
    QChartView *chartViewA = new QChartView();
    QChartView *chartViewB = new QChartView();


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


};
#endif // MAINWINDOW_H
