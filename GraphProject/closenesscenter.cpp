#include "closenesscenter.h"
#include<qalgorithms.h>
#include<QQueue>
#include<QStack>
#define INF 1e9
ClosenessCenter::ClosenessCenter(QVector<QVector<float> > adjacencyMatrix, QVector<QList<QPair<int, float> > > adjacencyList, int numberOfEdges)
{

     int n=adjacencyList.size();
   for (int i=0;i<adjacencyList.size();i++)
   {

       float res =shortest_distance(i,adjacencyList );
       my_data.push_back( float ( adjacencyList.size()-1 ) /res );

   }


}

void ClosenessCenter::getCentrality(QVector<float> ClosenessCenter)
{
    for (int i=0;i<my_data.size();i++)
    {
        ClosenessCenter.push_back(my_data[i]);
    }
}

float ClosenessCenter::shortest_distance(int src, QVector<QList<QPair<int,float>>> adjacencyList){



    int n = adjacencyList.size();
    QVector<int> d(n, INF);

QVector<int>Remaining_next_node;
QVector<int>Remaining_weight;
QVector<int>Remaining_pervious_node;
 QStack<int>current_node;



current_node.push(src);


int cur_dis=0 ;
  int counter =0;
  float distance=0;
  //int previous =0;
    while(make_sure(d) ||  !Remaining_next_node.empty()){

        QVector<int>next_node;
        QVector<float>weight;
        QVector<int>pervious_node;
        int cur_prev_node ;


        //int previous=current_node.head();//error
        int cur_node = current_node.top();//stack we top

        if (counter ==0){
             cur_dis =0;
             cur_prev_node=src ;
             counter ++;
        }
       // else {

        //int cur_prev_node = previous;
          // cur_dis +=distance ;   //edit here +=
          //  }

        if (d[cur_node]<cur_dis)
        {
           distance= trapped ( current_node,Remaining_pervious_node,Remaining_next_node,Remaining_weight,d,cur_dis);

            continue;
        }
        d[cur_node] = cur_dis;
       // p[cur_node] = cur_prev_node;

        // Add the nodes connected to current one
        for (int i=0;
             i< adjacencyList[cur_node].size();
             i++)
        {
            int temp1=adjacencyList[cur_node][i].first;
            float temp2=adjacencyList[cur_node][i].second;
            int temp3=cur_node;
            if (d[temp1] !=INF && d[temp1]<cur_dis+temp2)  //d[temp1]
                continue;


            next_node.push_back( temp1);
            weight.push_back( temp2);
            pervious_node.push_back(temp3);

        }


         if (!next_node.empty() || ! Remaining_weight.empty())
        distance= top(current_node,next_node,weight , Remaining_next_node
                      ,Remaining_weight,pervious_node,Remaining_pervious_node,d,cur_dis );
    }

    Remaining_next_node.clear();
    Remaining_weight.clear();
float result = 0;
    for (int i = 0; i < d.size(); i++)
    {
        result += d[i];
    }

    return result;

}



int ClosenessCenter::top(QStack<int>& current_node,QVector<int>&next_node,QVector<float>&weight ,
                         QVector<int>&Remaining_next_node,  QVector<int>&Remaining_weight,
                         QVector<int>&pervious_node,QVector<int>&Remaining_pervious_node,
                         QVector<int>&d,int&cur_dis)


{
    if (next_node.size()>0)
    {
    int flag=0;
    int min =weight[0];
    int i_index=0;

    for (int i=0;i<next_node.size();i++)
    {
        if (weight[i]<min)
        {

            i_index=i;
            min=weight[i];
        }


    }

    for (int i=0;i<next_node.size();i++)
    {
        if (i!=i_index)
        {
            Remaining_next_node.push_back(next_node[i]);
            Remaining_weight.push_back(weight[i]);
            Remaining_pervious_node.push_back(pervious_node[i]);
        }
    }


 int node=pervious_node[i_index];  // to get d of previous node
    int temp=0;

    if (! Remaining_next_node.empty())
    {
        for (int i=0;i<Remaining_next_node.size();i++)
        {
            int remaining_node=Remaining_pervious_node[i];

            if (Remaining_weight[i]+d[remaining_node]<min + d[node])
            {
                if (flag!=1){
                Remaining_next_node.push_back(next_node[i_index]);
                Remaining_weight.push_back(min);
                Remaining_pervious_node.push_back(pervious_node[i_index]);
                }

                temp=remaining_node;
                node=remaining_node;
                i_index=i;
                min=Remaining_weight[i];

               flag=1;


            }

        }



    }

if (flag==0)
{
current_node.push(next_node[i_index]);
cur_dis=min+d[node];
}
else {
    current_node.push(Remaining_next_node[i_index]);

    cur_dis= Remaining_weight[i_index]+d[temp];
    Remaining_pervious_node.remove(i_index);
    Remaining_weight.remove(i_index);
    Remaining_next_node.remove(i_index);
}

return min;
    }

    else {

       return trapped ( current_node,Remaining_pervious_node,Remaining_next_node,Remaining_weight,d,cur_dis);

    }


}




bool ClosenessCenter::make_sure(QVector<int>d)
{
    for (int i=0;i<d.size();i++)
    {
        if (d[i]==INF)
            return true;
    }
    return false ;
}


    int   ClosenessCenter::trapped ( QStack<int>& current_node,QVector<int>& Remaining_pervious_node
                                     ,QVector<int>& Remaining_next_node,
                                     QVector<int>& Remaining_weight,
                                     QVector<int> d, int &cur_dis)
{
        int perv_node=Remaining_pervious_node[0];
        int min =Remaining_weight[0];
        int next =Remaining_next_node[0];
        int i_index=0;
        for (int i=0;i<Remaining_next_node.size();i++)
        {
            int prev=Remaining_pervious_node[i];
            if (Remaining_weight[i]+d[prev]<min+d[perv_node] )
            {
                min=Remaining_weight[i];
                perv_node=Remaining_pervious_node[i];
                next=Remaining_next_node[i];
                i_index=i;
            }




        }
        current_node.push(next);
        cur_dis=min+d[perv_node];

        Remaining_weight.remove(i_index);
        Remaining_next_node.remove(i_index);
        Remaining_pervious_node.remove(i_index);
        return 0;


}


















