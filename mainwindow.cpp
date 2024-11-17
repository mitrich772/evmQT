#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include<iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <random>
#include <typeinfo>

#include <QLogValueAxis>
#include <QLineSeries>
#include <QValueAxis>
#include <QChart>
#include <QChartView>
#include <QStackedWidget>
#include <Qt>


using namespace std;
using namespace QtCharts;


const long MASLEN_A = 786432 * 8 * 10;  // 6 MB массив
const long MASLEN_B = 786432 * 8 * 10 * 8;
const long ELEMINPIXEL_A = (126000);
const long ELEMINPIXEL_B = (126000)*8;
const long SCALE = 500;
const long INDENT = 600;


long long sum = 0;
vector <int> index_arr (MASLEN_B);



template<class T>
void initArr(T a[], int length) {
    for (int i = 0; i < length; i++) {
        a[i] = rand() % 11;

    }
}

template<class T>
void directTraversal(T a[], int length) {
    long long sum = 0;
    long int ii = 0;
    for (int i = 0; i < length; i++) {
        sum += a[i];
        if (ii == length){
            break;
        }
        ii++;
    }

    cout << "Sum of direct traversal: " << sum << endl;
}

template<class T>
void reverseTraversal(T a[], int length) {
    long long sum = 0;
    long int ii = 0;
    for (int i = length-1; i >= 0; i--) {
        sum += a[i];
        if (ii == length){
            break;
        }
        ii++;
    }
    cout << "Sum of reverse traversal: " << sum << endl;
}

template<class T>
void stepTraversal(T a[], int length) {
    long long sum = 0;
    long int ii = 0;
    for (int i = 0; i < length; i += 1) {
        int index = i % length;
        sum += a[index];
        if (ii == length){
            break;
        }
        ii++;

    }
    cout << "Sum of stepped traversal: " << sum << endl;
}

template<class T>
void randomTraversal(T a[], int length) {

    int ii = 0;
    for (int i: index_arr) {
        if (ii == length){
            break;
        }
        sum += a[i];
        ii++;
    }

    cout << "Sum of rand traversal: " << sum << endl;
}

void drawChart(QChartView *view, QLineSeries *seriesDirect, QLineSeries *seriesReverse, QLineSeries *seriesStep, QLineSeries *seriesRandom){
    cout << "add series" <<endl;
    view->chart()->removeAllSeries();
    view->chart()->addSeries(seriesDirect);
    view->chart()->addSeries(seriesReverse);
    view->chart()->addSeries(seriesStep);
    view->chart()->addSeries(seriesRandom);
    cout << "set axis" <<endl;
    view->chart()->createDefaultAxes();
    view->chart()->axes(Qt::Horizontal).back()->setRange(0, 250);
    view->chart()->axes(Qt::Vertical).back()->setRange(0, 800);
    view->chart()->axes(Qt::Horizontal).back()->setTitleText("q []");
    view->chart()->axes(Qt::Vertical).back()->setTitleText("t [сек]");
    cout << "finished" <<endl;
}


void calculateA(QLineSeries *seriesDirectA, QLineSeries *seriesReverseA, QLineSeries *seriesStepA, QLineSeries *seriesRandomA){
    double previuosValueOfTime[4] = {0,0,0,0};
    void (*functions_A[4])(long long a[], int length) = {directTraversal, reverseTraversal, stepTraversal, randomTraversal};
    long startElements = 10000000;
    clock_t startTime;
    clock_t endTime;
    double seconds;
    qreal y2;
    qreal x2;
    qreal y1;
    qreal x1;
//    view->chart()->setTitle("Graphic A");
    static long long arr[MASLEN_A];

    initArr<long long>(arr, MASLEN_A);
    for(long elements = startElements; elements < MASLEN_A; elements += 10000000){
        for(int i = 0; i < 4; i++){
            startTime = clock();
            functions_A[i](arr, elements);
            endTime = clock();
            seconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
            y1 = 16 * previuosValueOfTime[i] * SCALE;
            x1 = (elements - 10000000) / ELEMINPIXEL_A;
            y2 = 16 * seconds * SCALE;
            x2 = elements / ELEMINPIXEL_A;
            cout << "(" << x1 << "," << y1 << ")" << "(" <<x2 << "," << y2 << ")" << endl;
            switch (i) {
            case 0:
                seriesDirectA->append(QPointF(x1, y1));
                seriesDirectA->append(QPointF(x2, y2));
                break;
            case 1:
                seriesReverseA->append(QPointF(x1, y1));
                seriesReverseA->append(QPointF(x2, y2));
                break;
            case 2:
                seriesStepA->append(QPointF(x1, y1));
                seriesStepA->append(QPointF(x2, y2));
                break;
            case 3:
                seriesRandomA->append(QPointF(x1, y1));
                seriesRandomA->append(QPointF(x2, y2));
                break;
            }

            previuosValueOfTime[i] = seconds; // запись времени для каждого метода
            //printf("The long long time: %f seconds\n", seconds,typeid(curFunc).name());
        }

    }

}
void calculateB(QLineSeries *seriesDirectB, QLineSeries *seriesReverseB, QLineSeries *seriesStepB, QLineSeries *seriesRandomB){
    double previuosValueOfTime[4] = {0,0,0,0};
    void (*functions_B[4])(char a[], int length) = {directTraversal, reverseTraversal, stepTraversal, randomTraversal};
    long startElements = 200;
    clock_t startTime;
    clock_t endTime;
    double seconds;
    qreal y2;
    qreal x2;
    qreal y1;
    qreal x1;


    static char a[MASLEN_B];

    initArr<char>(a, MASLEN_B);
    for(long elements = startElements; elements < MASLEN_B; elements = elements * 2){
        for(int i = 0; i < 4; i++){
            startTime = clock();
            //printf("%d/n",i);
            functions_B[i](a, elements);
            endTime = clock();
            seconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
            y1 = (16 * previuosValueOfTime[i])*SCALE;
            x1 = elements / 2/ELEMINPIXEL_B;
            y2 = 16 * seconds * SCALE;
            x2 = elements / ELEMINPIXEL_B;

            switch (i) {
            case 0:
                seriesDirectB->append(QPointF(x2, y2));
                seriesDirectB->append(QPointF(x2, y2));
                break;
            case 1:
                seriesReverseB->append(QPointF(x1, y1));
                seriesReverseB->append(QPointF(x2, y2));
                break;
            case 2:
                seriesStepB->append(QPointF(x1, y1));
                seriesStepB->append(QPointF(x2, y2));
                break;
            case 3:
                seriesRandomB->append(QPointF(x1, y1));
                seriesRandomB->append(QPointF(x2, y2));
                break;
            }
            previuosValueOfTime[i] = seconds; // запись времени для каждого метода
            //printf("The long long time: %f seconds\n", seconds,typeid(curFunc).name());
        }

    }
}




void shufleIndex(){
    for (int i = 0; i < MASLEN_B; i++) {
        index_arr[i] = i;
    }


    random_shuffle(index_arr.begin(), index_arr.end());
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->series_init();



    calculateA(seriesDirectA, seriesReverseA, seriesStepA, seriesRandomA);
    drawChart(this->chartViewA, seriesDirectA, seriesReverseA, seriesStepA, seriesRandomA);
    calculateB(seriesDirectB, seriesReverseB, seriesStepB, seriesRandomB);
    drawChart(this->chartViewB, seriesDirectB, seriesReverseB, seriesStepB, seriesRandomB);
    setCentralWidget(chartViewA);


}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_A){
        cout << "Left button" <<endl;
        QWidget *savedWidget = centralWidget();
        savedWidget->setParent(0);
        setCentralWidget(this->chartViewB);
    }
    if(e->key() == Qt::Key_D){
        cout << "Right button" <<endl;
        QWidget* savedWidget = centralWidget();
        savedWidget->setParent(0);
        setCentralWidget(this->chartViewA);
    }
}

