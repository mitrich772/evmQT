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
const long ELEMINPIXEL = 260000/3;
const long SIZEMULTIPLIER = 50;

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
    cout << "Sum: " << sum << endl;
}

template<class T>
void reversePas(T a[], int length) {
    long long sum = 0;
    for (int i = length-1; i >= 0; i--) {
        sum += a[i];
    }
    cout << "Sum: " << sum << endl;
}

template<class T>
void stepPas(T a[], int length) {
    long long sum = 0;
    for (int i = 0; i < length; i += 1) {
        int index = i % length;  // Используем остаток для сдвига по массиву
        sum += a[index];         // Суммируем элементы массива
    }
    cout << "Sum: " << sum << endl;
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

    cout << "Sum: " << sum << endl;
}

void calculate(QGraphicsScene *scene){

    void (*functions_A[4])(long long a[], int length) = {directPas, reversePas, stepPas, randomPas};
    long startElements = 20480;
    clock_t startTime;
    clock_t endTime;
    double seconds;
    qreal y;
    qreal x;

    static long long a[MASLEN_A];

    initMas<long long>(a, MASLEN_A);
    int i;
    for(long elements = startElements; elements < MASLEN_A; elements *= 2){
        i = 0;
        for(void (*curFunc)(long long a[], int length) : functions_A){
            startTime = clock();

            curFunc(a, elements);

            endTime = clock();
            seconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
            y = -16 * seconds * SIZEMULTIPLIER;
            x = (elements / ELEMINPIXEL);
            switch (i) {
            case 0:
                scene->addLine(
                    QLineF(x, y, x, y),
                    QPen(Qt::red, 5)
                    );
                break;
            case 1:
                scene->addLine(
                    QLineF(x, y, x, y),
                    QPen(Qt::blue, 3)
                    );
            case 2:
                scene->addLine(
                    QLineF(x, y, x, y),
                    QPen(Qt::green, 2)
                    );
            case 3:
                scene->addLine(
                    QLineF(x, y, x, y),
                    QPen(Qt::black, 3)
                    );
                break;
            }

            //printf("The long long time: %f seconds\n", seconds,typeid(curFunc).name());
            i++;
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->addLine(0,0,500,0);
    scene->addLine(0,0,0,-500);

    calculate(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

