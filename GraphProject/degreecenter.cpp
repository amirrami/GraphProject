#include "degreecenter.h"

DegreeCenter::DegreeCenter(QVector<QVector<float> > adjacencyMatrix, QVector<QList<QPair<int, float> > > adjacencyList, int numberOfEdges)
{

    for (int i=0;i<adjacencyList.size();i++)
    {
       my_data.push_back(adjacencyList[i].size());
    }
}

void DegreeCenter::getCentrality(QVector<float> DegreeCenter)
{
    for (int i=0;i<my_data.size();i++)
       DegreeCenter.push_back(my_data[i]);

}
