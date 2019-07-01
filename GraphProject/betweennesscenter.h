#ifndef BETWEENNESSCENTER_H
#define BETWEENNESSCENTER_H

#include <QVector>
#include <QList>
#include <QPair>


class betweennessCenter
{
public:
    QVector<float>my_data;

    QVector <QVector<int>> getparent(QVector<QList<QPair<int, float> > > adjacencyList, int src);

    //void printparent(QVector <QSet<int>> parent, int des, int des1);
    bool checkparents(QVector <QVector<int>> parent, int node);
    bool isbetween(int des, int node, QVector <QVector<int>> parent);
    int calcinter(int des, int node, QVector <QVector<int>> parent);
    int shortestpaths(int des, QVector <QVector<int>> parent);
    float betweeness(int node, QVector<QList<QPair<int, float> > > adjacencyList);


    betweennessCenter(QVector<QVector<float>> adjacencyMatrix,QVector<QList<QPair<int,float>>> adjacencyList,int numberOfEdges);
    void getCentrality(QVector<float> betweennessCenter);

    int trapped ( QStack<int>& current_node,QVector<int>& Remaining_pervious_node
                                     ,QVector<int>& Remaining_next_node,
                                     QVector<int>& Remaining_weight,
                                     QVector<int> d, int &cur_dis,QStack<int>& parent_node );

    bool make_sure(QVector<int>d);
   int top (QStack<int>& current_node,QVector<int>&next_node,QVector<float>&weight ,
            QVector<int>&Remaining_next_node,  QVector<int>&Remaining_weight,
            QVector<int>&pervious_node,QVector<int>&Remaining_pervious_node,
            QVector<int>&d,int&cur_dis,QStack<int>& parent_node);



};

#endif // BETWEENNESSCENTER_H
