#ifndef BETWEENNESSCENTER_H
#define BETWEENNESSCENTER_H

#include <QVector>
#include <QList>
#include <QPair>

class betweennessCenter
{
public:
    betweennessCenter(QVector<QVector<float>> adjacencyMatrix,QVector<QList<QPair<int,float>>> adjacencyList,int numberOfEdges);
    void getCentrality(QVector<float> betweennessCenter);
};

#endif // BETWEENNESSCENTER_H
