#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QGraphicsScene>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QList>
#include <QPair>

#include "graphics.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void InitUI();
    void InitFisrtPage();
    void extractInput(QString lineInput,int &start,int &destination,int &weight);
public slots:
    void browseButtonPressed();
    void runAlgorithmPressed();

private:
    Ui::MainWindow *ui;
    QWidget *centralWidget;
    Graphics *Graph;
    QGraphicsScene *scene;
    //colors and pallete
    QPalette *mainPalette;
    //layout
    QFormLayout *firstInputPage;
    QHBoxLayout *mainLayout;
    QHBoxLayout *inputLayout;
    QHBoxLayout *graphicsLayout;
    // buttons
    QPushButton *browseButton;
    QPushButton *RunButton;
    //comboBox
    QComboBox *algorithm;
    //label
    QLabel *chooseAlgorithm;
    //text
    QLineEdit *fileName;

    int numberOfNodes,numberOfEdges;
    QVector< QVector<float> >adjacencyMatrix;
    QVector< QList< QPair<int,float> > >adjacencyList;
    QVector<float> centrality;





};

#endif // MAINWINDOW_H
