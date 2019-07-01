#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>
#include <QMessageBox>
#include "betweennesscenter.h"
#include "closenesscenter.h"
#include "degreecenter.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->removeToolBar(ui->mainToolBar);
    this->statusBar()->setVisible(false);
    mainPalette = new QPalette;
    this->setWindowTitle("Social Network Analysis");
    mainPalette->setColor(QPalette::Active,QPalette::Window,Qt::white);
    this->setPalette(*mainPalette);
    InitUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUI()
{

    //init graph layout

    //init input layout
    inputLayout = new QHBoxLayout;
    InitFisrtPage();
    mainLayout = new QHBoxLayout;
    mainLayout->addItem(inputLayout);


    //adding main layout to central widget of window
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
}

void MainWindow::InitFisrtPage(){

    QFont font("Volkhov",11,QFont::Light,true);
    chooseAlgorithm = new QLabel("Choose Algorithm");
    chooseAlgorithm->setFont(font);

    browseButton = new QPushButton;
    browseButton->setText("Browse Input File");
    browseButton->setMinimumHeight(30);
    browseButton->setFont(font);

    RunButton = new QPushButton;
    RunButton->setText("Run Algorithm");
    RunButton->setMinimumHeight(30);
    RunButton->setFont(font);

    algorithm = new QComboBox;
    algorithm->addItem("Degree Centrality");
    algorithm->addItem("Closeness Centrality");
    algorithm->addItem("Betweenness Centrality");
    algorithm->setMaximumHeight(30);
    algorithm->setFont(font);

    fileName = new QLineEdit;
    fileName->setDisabled(true);
    fileName->setFont(font);
    fileName->setMinimumHeight(30);

    firstInputPage = new QFormLayout;
    firstInputPage->addRow(fileName,browseButton);
    firstInputPage->addRow(chooseAlgorithm,algorithm);
    firstInputPage->addRow(RunButton);

    firstInputPage->setContentsMargins(10,10,10,10);
    firstInputPage->setSpacing(10);
    inputLayout->addItem(firstInputPage);
    QObject::connect(browseButton,SIGNAL(clicked()),this,SLOT(browseButtonPressed()));
    QObject::connect(RunButton,SIGNAL(clicked()),this,SLOT(runAlgorithmPressed()));

}

void MainWindow::extractInput(QString lineInput,int &start, int &destination, int &weight)
{
    int numberFlag = 0;
    QString number="";
    for(int i=0 ;i<lineInput.length();i++){
        if(lineInput[i]!=' ')
            number+=lineInput[i];
        else if(lineInput[i]==' '){
            if(numberFlag==0)
                start = number.toInt();
            else if(numberFlag==1)
                destination = number.toInt();
            else if(numberFlag==2)
                break;
            numberFlag++;
            number="";
        }
    }
    weight = number.toInt();
    return;
}

void MainWindow::browseButtonPressed()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Choose input file","c://",tr("Text Files (*.txt)"));
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    else{
        QTextStream input(&file);
        QString text = input.readLine();

        QString number = "";
        for(int i=0 ;i<text.length();i++){
            if(text[i]!=' ')
                number+=text[i];
            else if(text[i]==' '){
                numberOfNodes = number.toInt();
                number="";
            }
        }
        numberOfEdges = number.toInt();

        if(numberOfNodes <=0 || numberOfEdges <=0 )
            QMessageBox::warning(this,"Input File Error","Please Select A Valid Input Text File");
        else
        {
            fileName->setText(file_name);
            adjacencyMatrix.resize(numberOfNodes);
            adjacencyList.resize(numberOfNodes);
            for(int i=0;i<adjacencyMatrix.size();i++){
                adjacencyMatrix[i].resize(numberOfNodes);
            }
            int start,destination,weight;
            for(int i=0;i<numberOfEdges;i++){
                text = input.readLine();
                extractInput(text,start,destination,weight);
                QPair<int,int> node;
                node.first=destination;
                node.second=weight;
                adjacencyList[start].push_back(node);
                node.first = start;
                adjacencyList[destination].push_back(node);
                adjacencyMatrix[start][destination] = weight;
                adjacencyMatrix[destination][start] = weight;
            }
        }

    }
    file.close();

}

void MainWindow::runAlgorithmPressed()
{
    if(algorithm->currentText()=="Degree Centrality"){
        DegreeCenter centralityAlgorithm(adjacencyMatrix,adjacencyList,numberOfEdges);
        Graph = new Graphics(0);
        Graph->show();
        Graph->drawNodes(adjacencyList,centralityAlgorithm.my_data,"Degree Centrality");
        adjacencyMatrix.clear();
        adjacencyList.clear();
        fileName->setText("");
    }
    else if (algorithm->currentText()=="Closeness Centrality") {
        ClosenessCenter centralityAlgorithm(adjacencyMatrix,adjacencyList,numberOfEdges);
        Graph = new Graphics(0);
        Graph->show();
        Graph->drawNodes(adjacencyList,centralityAlgorithm.my_data,"Closeness Centrality");
        adjacencyMatrix.clear();
        adjacencyList.clear();
        fileName->setText("");
    }
    else if (algorithm->currentText()=="Betweenness Centrality") {
        betweennessCenter centralityAlgorithm(adjacencyMatrix,adjacencyList,numberOfEdges);
        Graph = new Graphics(0);
        Graph->show();
        Graph->drawNodes(adjacencyList,centralityAlgorithm.my_data,"Betweenness Centrality");
        adjacencyMatrix.clear();
        adjacencyList.clear();
        fileName->setText("");

    }
}


