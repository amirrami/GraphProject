#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <list>
#include <utility>
#include <cstdlib>
#include <queue> 
#include <set>
#include <iomanip>

#define INF 9999
#define NULL -1
#define ZERO 0
using namespace std;


vector <vector<int>> getparent(vector<vector<pair<int, int>>> adjlist, int src);
vector <set<int>> getparent1(vector<vector<pair<int, int>>> adjlist, int src);
void printparent(vector <vector<int>> parent, int des);
void printparent(vector <set<int>> parent, int des, int des1);
bool checkparents(vector <vector<int>> parent, int node);
bool isbetween(int des, int node, vector <vector<int>> parent);
int calcinter(int des, int node, vector <vector<int>> parent);
int shortestpaths(int des, vector <vector<int>> parent);
double betweeness(int node, vector<vector<pair<int, int>>> adjlist);






int main()
{
	int n,node1,node2,weight,k,i,inter=0;
	

	cin >> n>> k;
	vector<vector<pair<int, int>>> test(n, vector<pair<int, int>>());
	vector <vector<int>> parent(n);
	for (i = 0; i < k; i++)
	{
		cin >> node1 >> node2 >> weight;
		test[node1].push_back({node2,weight});
		test[node2].push_back({node1,weight});
	}
	for (i = 0; i < n; i++)
	{
		cout <<setprecision(12)<< betweeness(i, test)<<"\n";
	}

	//parent = getparent(test, 1);
	//cout<<isbetween(2, 3, parent);






	return ZERO;
}

//vector<list<pair<int,int>>>adjlist(n,list<pair<int,int>>());

vector <vector<int>> getparent(vector<vector<pair<int, int>>> adjlist, int src)
{
	priority_queue <pair <int, pair <int, int> >, vector<pair <int, pair <int, int> > >, greater <pair <int, pair <int, int> >>>nodes_q;
    
		
	int n = adjlist.size();
	vector<int> distance(n, INF);
	vector <vector<int>> parent(n);
	nodes_q.push({ ZERO , {src,src} });

	while(!nodes_q.empty()) {
		pair <int, pair <int, int> >p = nodes_q.top();
		nodes_q.pop();
		int curnode= p.second.first;
		int curprevnode = p.second.second;
		int curdis = p.first;
		if (distance[curnode] < curdis)
		{
			continue;
		}
		distance[curnode] = curdis;
		parent[curnode].push_back(curprevnode);

		for (int i = ZERO ;i < adjlist[curnode].size();i++)
		{
			if (adjlist[curnode][i].first==NULL)
				continue;
			int nextnode = adjlist[curnode][i].first;
			int weight = adjlist[curnode][i].second;
			if(distance[nextnode] < curdis + weight)
				continue;
			nodes_q.push({ curdis + weight ,{ nextnode ,curnode } });

		}
	}
	return parent;




}
vector <set<int>> getparent1(vector<vector<pair<int, int>>> adjlist, int src)
{
	priority_queue <pair <int, pair <int, int> >, vector<pair <int, pair <int, int> > >, greater <pair <int, pair <int, int> >>>nodes_q;


	int n = adjlist.size();
	vector<int> distance(n, INF);
	vector <set<int>> parent(n);
	nodes_q.push({ ZERO , {src,src} });

	while (!nodes_q.empty()) {
		pair <int, pair <int, int> >p = nodes_q.top();
		nodes_q.pop();
		int curnode = p.second.first;
		int curprevnode = p.second.second;
		int curdis = p.first;
		if (distance[curnode] < curdis)
		{
			continue;
		}
		distance[curnode] = curdis;
		parent[curnode].insert(curprevnode);

		for (int i = ZERO; i < adjlist[curnode].size(); i++)
		{
			if (adjlist[curnode][i].first == NULL)
				continue;
			int nextnode = adjlist[curnode][i].first;
			int weight = adjlist[curnode][i].second;
			if (distance[nextnode] < curdis + weight)
				continue;
			nodes_q.push({ curdis + weight ,{ nextnode ,curnode } });

		}
	}
	return parent;




}

void printparent(vector <vector<int>> parent,int des)
{
	if (parent[des][0] == des)
	{

		return;
	}
	for (int i=0; i<parent[des].size(); i++)
	{
		printparent(parent, parent[des][i]);
		cout << parent[des][i];

	}
	return;
}
void printparent(vector <set<int>> parent, int des , int des1)
{
	set<int>::iterator it;
	it = parent[des].begin();
	if (*it == des)
	{
		cout << endl;
		return;
	}
	
	for (it = parent[des].begin(); it != parent[des].end(); it++)
	{
		printparent(parent, *it,des1);
		cout << *it;
		if (des == des1) cout << endl;

	}
	

	return;
}

double betweeness(int node, vector<vector<pair<int, int>>> adjlist )
{
	vector <vector<int>> parent;
	int n = adjlist.size(),i,j,inter,paths;
	double bet = 0;
	for (i = 0; i < n; i++)
	{
		if (i == node)continue;
		parent = getparent(adjlist, i);
		if (!checkparents(parent, node))continue;
		for (j = i+1; j < n; j++)
		{
			if (isbetween(j,node,parent))
			{
				inter=calcinter(j,node,parent);
				paths = shortestpaths(j, parent);
				bet += ((double)inter/paths);
			}


		}


	}
	return bet;
}
bool checkparents(vector <vector<int>> parent,int node)
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
bool isbetween(int des,int node, vector <vector<int>> parent)
{
	int i,is=0;
	

	if (node == des) return 1;
	if (des == parent[des][0]) return 0;
    for ( i =0; i<parent[des].size(); i++)
	{
		if(is= isbetween(parent[des][i], node, parent))return 1;
	}
}
int calcinter(int des, int node, vector <vector<int>> parent)
{
	int i, n = parent.size(), inter=0 ;
	
	if (*(parent[des].begin()) == des)return 0;
	for (int it = 0; it<parent[des].size(); it++)
	{

		if (parent[des][it] == node)
		{
			inter++;

		}
		else if ((it != 0&&parent[des][it]== parent[des][it-1]))continue;
		else
		{
			inter += calcinter(parent[des][it], node, parent);
		}

	}
	return inter;
}
int shortestpaths(int des, vector <vector<int>> parent)
{
	int i,path=0;
	if (des == parent[des][0])return 1;
	for (i = 0; i < parent[des].size(); i++)
	{
	 if ((i != 0 && parent[des][i] == parent[des][i - 1]))continue;

		path += shortestpaths(parent[des][i], parent);
	}
	return path;

}