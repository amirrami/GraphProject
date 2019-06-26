#ifndef CLOSENESSCENTER_H
#define CLOSENESSCENTER_H

#include <QVector>
#include <QList>
#include <QPair>

class ClosenessCenter
{
public:
    ClosenessCenter(QVector<QVector<float>> adjacencyMatrix,QVector<QList<QPair<int,float>>> adjacencyList,int numberOfEdges);
    void getCentrality(QVector<float> ClosenessCenter);
};

#endif // CLOSENESSCENTER_H
