#ifndef CLOSENESSCENTER_H
#define CLOSENESSCENTER_H

#include <QVector>
#include <QList>
#include <QPair>

class ClosenessCenter
{
public:
    bool make_sure(QVector<int>d);
   int top (QStack<int>& current_node,QVector<int>&next_node,QVector<float>&weight ,
            QVector<int>&Remaining_next_node,  QVector<int>&Remaining_weight,
            QVector<int>&pervious_node,QVector<int>&Remaining_pervious_node,
            QVector<int>&d,int&cur_dis);
    float shortest_distance(int src, QVector<QList<QPair<int,float>>> adjacencyList);
    QVector<float>my_data;
    ClosenessCenter(QVector<QVector<float>> adjacencyMatrix,QVector<QList<QPair<int,float>>> adjacencyList,int numberOfEdges);
    void getCentrality(QVector<float> ClosenessCenter);

    int trapped ( QStack<int>& current_node,QVector<int>& Remaining_pervious_node
                                     ,QVector<int>& Remaining_next_node,
                                     QVector<int>& Remaining_weight,
                                     QVector<int> d, int &cur_dis);

};

#endif // CLOSENESSCENTER_H
