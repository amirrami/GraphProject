#include "betweennesscenter.h"
#include<QQueue>
#include<QStack>
#define INF 9999
#define NUL -1
#define ZERO 0

betweennessCenter::betweennessCenter(QVector<QVector<float> > adjacencyMatrix, QVector<QList<QPair<int, float> > > adjacencyList, int numberOfEdges)
{
    for (int i=0;i<adjacencyList.size();i++)
    my_data.push_back(betweeness(i, adjacencyList));


}

void betweennessCenter::getCentrality(QVector<float> betweennessCenter)
{
    for (int i=0;i<my_data.size();i++)
    betweennessCenter.push_back(my_data[i]);

}


float betweennessCenter:: betweeness(int node, QVector<QList<QPair<int, float> > > adjlist )
{
    QVector <QVector<int>> parent;
    int n = adjlist.size(),i,j,inter,paths;
    float bet = 0;
    for (i = 0; i < n; i++)
    {
        if (i==node)
            continue;
        parent = getparent(adjlist, i);
        if (!checkparents(parent, node))continue;
        for (j = i+1; j < n; j++)
        {
            if (isbetween(j,node,parent))
            {
                inter=calcinter(j,node,parent);
                paths = shortestpaths(j, parent);
                bet += float (inter)/  paths;
            }


        }


    }
    return bet;
}



bool betweennessCenter:: checkparents(QVector <QVector<int>> parent,int node)
{
    int i,n= parent.size(),it;

        for (i = 0; i < n; i++)
        {
            for (it = 0; it<parent[i].size(); it++)
            {
                if (parent[i][it] == node)
                    return 1;
            }

        }
    return 0;
}


bool betweennessCenter:: isbetween(int des,int node, QVector <QVector<int>> parent)
{
    int i;


    if (node == des) return true;
    if (des == parent[des][0]) return false;
    for ( i =0; i<parent[des].size(); i++)
    {
        if(isbetween(parent[des][i], node, parent))
            return true;
    }
    return false ;// laaazm nt2aakd
}




int betweennessCenter:: calcinter(int des, int node, QVector <QVector<int>> parent)
{
    int inter=0 ;

    if (*(parent[des].begin()) == des)
        return 0;
    for (int it = 0; it<parent[des].size(); it++)
    {

        if (parent[des][it] == node)
        {
            inter++;

        }
        else if ((it != 0&&parent[des][it]== parent[des][it-1]))
            continue;
        else
        {
            inter += calcinter(parent[des][it], node, parent);
        }

    }
    return inter;
}






int betweennessCenter:: shortestpaths(int des, QVector <QVector<int>> parent)
{
    int i,path=0;
    if (des == parent[des][0])return 1;
    for (i = 0; i < parent[des].size(); i++)
    {
     if ((i != 0 && parent[des][i] == parent[des][i - 1]))
         continue;

        path += shortestpaths(parent[des][i], parent);
    }
    return path;

}






QVector <QVector<int>>betweennessCenter:: getparent(QVector<QList<QPair<int, float> > > adjacencyList, int src)
{
int n = adjacencyList.size();
QVector<int> d(n, INF);
QVector <QVector<int>>parent(n);

QVector<int>Remaining_next_node;
QVector<int>Remaining_weight;
QVector<int>Remaining_pervious_node;
QStack<int>current_node;
QStack<int>parent_node;



current_node.push(src);
parent_node.push(src);


int cur_dis=0 ;
int counter =0;
float distance=0;
//int previous =0;
while(make_sure(d) ||  !Remaining_next_node.empty()){

    QVector<int>next_node;
    QVector<float>weight;
    QVector<int>pervious_node;




    int cur_node = current_node.top();
    if (counter ==0){
         cur_dis =0;

         counter ++;
    }


    if (d[cur_node]<cur_dis)
    {
       distance= trapped ( current_node,Remaining_pervious_node,Remaining_next_node,Remaining_weight,d,cur_dis ,parent_node);

        continue;
    }
    if (d[cur_node]==cur_dis && cur_node!=src)
    {
        parent[cur_node].push_back(parent_node.top());

    }

    d[cur_node] = cur_dis;
   parent[cur_node].push_back(parent_node.top());

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
                  ,Remaining_weight,pervious_node,Remaining_pervious_node,d,cur_dis ,parent_node);
}

Remaining_next_node.clear();
Remaining_weight.clear();
if (d[current_node.top()]==cur_dis && current_node.top()!=src)
{
    parent[current_node.top()].push_back(parent_node.top());

}

for (int i=0;i<parent.size();i++) // remove any similar added values
{

    if (i==src)
        continue;

    if (parent[i].size()==1)
        continue;

    for (int j=0;j<parent[i].size()-1;j++)
    {
        for (int k=j+1;k<parent[i].size();k++ )
        {
            if (parent[i][j]==parent[i][k])
                parent[i].remove(k);

        }

    }

}



return parent  ;

}



int betweennessCenter::top(QStack<int>& current_node,QVector<int>&next_node,QVector<float>&weight ,
                     QVector<int>&Remaining_next_node,  QVector<int>&Remaining_weight,
                     QVector<int>&pervious_node,QVector<int>&Remaining_pervious_node,
                     QVector<int>&d,int&cur_dis ,QStack<int>& parent_node )


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
parent_node.push(pervious_node[i_index]);
cur_dis=min+d[node];
}
else {
current_node.push(Remaining_next_node[i_index]);
parent_node.push(Remaining_pervious_node[i_index]);

cur_dis= Remaining_weight[i_index]+d[temp];
Remaining_pervious_node.remove(i_index);
Remaining_weight.remove(i_index);
Remaining_next_node.remove(i_index);
}

return min;
}

else {

   return trapped ( current_node,Remaining_pervious_node,Remaining_next_node,Remaining_weight,d,cur_dis,parent_node);

}


}




bool betweennessCenter::make_sure(QVector<int>d)
{
for (int i=0;i<d.size();i++)
{
    if (d[i]==INF)
        return true;
}
return false ;
}


int   betweennessCenter::trapped ( QStack<int>& current_node,QVector<int>& Remaining_pervious_node
                                 ,QVector<int>& Remaining_next_node,
                                 QVector<int>& Remaining_weight,
                                 QVector<int> d, int &cur_dis
                                   ,QStack<int>& parent_node )
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
    parent_node.push(perv_node);
    cur_dis=min+d[perv_node];

    Remaining_weight.remove(i_index);
    Remaining_next_node.remove(i_index);
    Remaining_pervious_node.remove(i_index);
    return 0;


}










