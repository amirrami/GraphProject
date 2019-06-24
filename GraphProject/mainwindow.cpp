#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->removeToolBar(ui->mainToolBar);
    this->statusBar()->setVisible(false);
    mainPalette = new QPalette;
    this->setWindowTitle("Memory Management Algorithms");
    mainPalette->setColor(QPalette::Active,QPalette::Window,Qt::white);
    this->setPalette(*mainPalette);
}

MainWindow::~MainWindow()
{
    delete ui;
}
