#include <QDebug>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tomographer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int x = TestSimpleParameters(1,2);
    qInfo()<<"TestSimpleParameters(1,2)="<<x;
    int y = TestStringParameters("foobar");
    qInfo()<<"TestStringParameters('foobar')="<<y;

    //extern "C" DllExport int TestSimpleParameters(int p0, int p1);
    //Demonstrates how to pass strings and get something from them like the size
    //extern "C" DllExport int TestStringParameters(const char* myStr);
    //Demonstrates how get a list of structs as a function return
    //extern "C" DllExport SomeData* TestGetStruct(int amount);
    //Demonstrates how to pass a function.
    //extern "C" DllExport void TestCallback(SimpleCallback cbk);

}

MainWindow::~MainWindow()
{
    delete ui;
}

