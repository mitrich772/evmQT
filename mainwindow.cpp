#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include<iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <random>
#include <typeinfo>
using namespace std;

const long MASLEN_A = 786432 * 8 * 10;  // 6 MB массив
const long MASLEN_B = 786432 * 8 * 10 * 8;
const long ELEMINPIXEL_A = (126000);
const long ELEMINPIXEL_B = (126000)*8;
const long SIZEMULTIPLIER = 50;
const long INDENT = 600;

// Глобальный массив

template<class T>
void initMas(T a[], int length) {
    for (int i = 0; i < length; i++) {
        a[i] = rand() % 11;
    }
}

template<class T>
void directPas(T a[], int length) {
    long long sum = 0;
    for (int i = 0; i < length; i++) {
        sum += a[i];
    }
    cout << "Sum direct: " << sum << endl;
}

template<class T>
void reversePas(T a[], int length) {
    long long sum = 0;
    for (int i = length-1; i >= 0; i--) {
        sum += a[i];
    }
    cout << "Sum reverse: " << sum << endl;
}

template<class T>
void stepPas(T a[], int length) {
    long long sum = 0;
    for (int i = 0; i < length; i += 1) {
        int index = i % length;  // Используем остаток для сдвига по массиву
        sum += a[index];         // Суммируем элементы массива
    }
    cout << "Sum step: " << sum << endl;
}

template<class T>
void randomPas(T a[], int length) {
    long long sum = 0;

    // Создаем вектор индексов от 0 до length-1
    vector<int> indices(length);
    for (int i = 0; i < length; i++) {
        indices[i] = i;
    }

    // Перемешиваем индексы (алгоритм Фишера-Йетса)
    random_device rd;   // Для генерации случайного числа
    mt19937 g(rd());    // Создаем генератор случайных чисел
    shuffle(indices.begin(), indices.end(), g);

    // Обход массива по случайным индексам
    for (int i = 0; i < length; i++) {
        sum += a[indices[i]];  // Доступ к элементам по случайным индексам
    }

    cout << "Sum rand: " << sum << endl;
}

void calculateA(QGraphicsScene *scene){
    double previuosValueOfTime[4] = {0,0,0,0};
    void (*functions_A[4])(long long a[], int length) = {directPas, reversePas, stepPas, randomPas};
    long startElements = 10000000;
    clock_t startTime;
    clock_t endTime;
    double seconds;
    qreal y2;
    qreal x2;
    qreal y1;
    qreal x1;

    static long long a[MASLEN_A];

    initMas<long long>(a, MASLEN_A);
    int i;
    for(long elements = startElements; elements < MASLEN_A; elements += 10000000){
        i = 0;
        for(void (*curFunc)(long long a[], int length) : functions_A){
            startTime = clock();
            //printf("%d/n",i);
            curFunc(a, elements);
            endTime = clock();
            seconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
            y1 = -16 * previuosValueOfTime[i] * SIZEMULTIPLIER;
            x1 = ((elements - 10000000) / ELEMINPIXEL_A);
            y2 = -16 * seconds * SIZEMULTIPLIER;
            x2 = (elements / ELEMINPIXEL_A);

            switch (i) {
            case 0:
                scene->addLine(
                    QLineF(x1, y1, x2, y2),
                    QPen(Qt::red, 2)
                    );
                break;
            case 1:
                scene->addLine(
                    QLineF(x1, y1, x2, y2),
                    QPen(Qt::green, 2)
                    );
                break;
            case 2:
                scene->addLine(
                    QLineF(x1, y1, x2, y2),
                    QPen(Qt::blue, 2)
                    );
                break;
            case 3:
                scene->addLine(
                    QLineF(x1, y1, x2, y2),
                    QPen(Qt::yellow, 2)
                    );
                break;
            }
            scene->addLine(
                QLineF(x2, y2, x2, y2),
                QPen(Qt::black, 5)
                );

            previuosValueOfTime[i] = seconds; // запись времени для каждого метода
            //printf("The long long time: %f seconds\n", seconds,typeid(curFunc).name());
            i++;
        }
    }

}
void calculateB(QGraphicsScene *scene){
    double previuosValueOfTime[4] = {0,0,0,0};
    void (*functions_B[4])(char a[], int length) = {directPas, reversePas, stepPas, randomPas};
    long startElements = 200;
    clock_t startTime;
    clock_t endTime;
    double seconds;
    qreal y2;
    qreal x2;
    qreal y1;
    qreal x1;

    static char a[MASLEN_B];

    initMas<char>(a, MASLEN_B);
    int i;
    for(long elements = startElements; elements < MASLEN_B; elements = elements * 2){
        i = 0;
        for(void (*curFunc)(char a[], int length) : functions_B){
            startTime = clock();
            //printf("%d/n",i);
            curFunc(a, elements);
            endTime = clock();
            seconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
            y1 = (-16 * previuosValueOfTime[i] * SIZEMULTIPLIER);
            x1 = ((elements / 2) / ELEMINPIXEL_B)+INDENT;
            y2 = -16 * seconds * SIZEMULTIPLIER;
            x2 = (elements / ELEMINPIXEL_B)+INDENT;

            switch (i) {
            case 0:
                scene->addLine(
                    QLineF(x1, y1, x2, y2),
                    QPen(Qt::red, 2)
                    );
                break;
            case 1:
                scene->addLine(
                    QLineF(x1, y1, x2, y2),
                    QPen(Qt::green, 2)
                    );
                break;
            case 2:
                scene->addLine(
                    QLineF(x1, y1, x2, y2),
                    QPen(Qt::blue, 2)
                    );
                break;
            case 3:
                scene->addLine(
                    QLineF(x1, y1, x2, y2),
                    QPen(Qt::yellow, 2)
                    );
                break;
            }
            scene->addLine(
                QLineF(x2, y2, x2, y2),
                QPen(Qt::black, 5)
                );

            previuosValueOfTime[i] = seconds; // запись времени для каждого метода
            //printf("The long long time: %f seconds\n", seconds,typeid(curFunc).name());
            i++;
        }
    }
}

void drawAxis(QGraphicsScene *scene){
    scene->addLine(0,0,500,0,QPen(Qt::black, 4));
    scene->addLine(0,0,0,-500,QPen(Qt::black, 4));
    scene->addLine(600,0,1100,0,QPen(Qt::black, 4));
    scene->addLine(600,0,600,-500,QPen(Qt::black, 4));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    drawAxis(scene);
    calculateA(scene);
    calculateB(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

