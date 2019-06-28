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

#define INF 9999
#define NULL -1
#define ZERO 0
using namespace std;


vector <list<int>> getparent(vector<vector<pair<int, int>>> adjlist, int src);
vector <set<int>> getparent1(vector<vector<pair<int, int>>> adjlist, int src);
void printparent(vector <list<int>> parent, int des);
void printparent(vector <set<int>> parent, int des, int des1);
bool checkparents(vector <list<int>> parent, int node);
bool isbetween(int des, int node, vector <list<int>> parent);
int calcinter(int des, int node, vector <list<int>> parent);





int main()
{
	int n,node1,node2,weight,k,i,inter=0;
	

	cin >> n>> k;
	vector<vector<pair<int, int>>> test(n, vector<pair<int, int>>());
	vector <list<int>> parent(n);
	for (i = 0; i < k; i++)
	{
		cin >> node1 >> node2 >> weight;
		test[node1].push_back({node2,weight});
		test[node2].push_back({node1,weight});
	}
	parent = getparent(test,0);
	cout << calcinter(9, 3, parent);






	return ZERO;
}

//vector<list<pair<int,int>>>adjlist(n,list<pair<int,int>>());

vector <list<int>> getparent(vector<vector<pair<int, int>>> adjlist, int src)
{
	priority_queue <pair <int, pair <int, int> >, vector<pair <int, pair <int, int> > >, greater <pair <int, pair <int, int> >>>nodes_q;
    
		
	int n = adjlist.size();
	vector<int> distance(n, INF);
	vector <list<int>> parent(n);
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

void printparent(vector <list<int>> parent,int des)
{
	if (parent[des].front() == des)
	{

		return;
	}
	list<int>::iterator it ;
	for (it = parent[des].begin(); it != parent[des].end(); it++)
	{
		printparent(parent, *it);
		cout << *it;

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

/*float betweeness(int node, vector<vector<pair<int, int>>> adjlist )
{
	vector <list<int>> parent;
	int n = adjlist.size(),i,j,inter;
	float bet = 0;
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
			}


		}


	}

}*/
bool checkparents(vector <list<int>> parent,int node)
{
	int i,n= parent.size();
    list<int>::iterator it;
		for (i = 0; i < n; i++)
		{
			for (it = parent[i].begin(); it != parent[i].end(); it++)
			{
				if (*it == node)
					return 1;
			}
			
		}
	return 0;
}
bool isbetween(int des,int node, vector <list<int>> parent)
{
	int i, n = parent.size(),chk=des;
	list<int>::iterator it;

	if (node == des)
	{
		return 1;
	}
	for (it = parent[des].begin(); it != parent[des].end(); it++)
	{
		return isbetween(*it, node, parent);
	}
	
}
int calcinter(int des, int node, vector <list<int>> parent)
{
	int i, n = parent.size(), inter=0 ;
	list<int>::iterator it;
	if (*(parent[des].begin()) == des)return 0;
	for (it = parent[des].begin(); it != parent[des].end(); ++it)
	{

		if (*it == node)
		{
			inter++;

		}
		else if (*it==*(it--)&& (it) != parent[des].begin())it++;
		else
		{
			inter += calcinter(*it, node, parent);
		}

	}
	return inter;
}