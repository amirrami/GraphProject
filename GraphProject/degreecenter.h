#ifndef DEGREECENTER_H
#define DEGREECENTER_H

#include <QVector>
#include <QList>
#include <QPair>

class DegreeCenter
{
public:
    QVector<float>my_data;
    DegreeCenter(QVector<QVector<float>> adjacencyMatrix,QVector<QList<QPair<int,float>>> adjacencyList,int numberOfEdges);
    void getCentrality(QVector<float> DegreeCenter);
};

#endif // DEGREECENTER_H
