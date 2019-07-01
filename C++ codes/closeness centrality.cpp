#include <vector>
#include <cctype>
#include <cstdlib>
#include<map>
#include<queue>
#include <iostream>
#include<fstream>
#include <iomanip> 
#define INF 10000000 
using namespace std;
int shortest_distance(int src,
	vector<vector<pair<int, int> > > &adj_list);

int main()
{

	int Number_nodes, Number_edges;
	
	
		cin >> Number_nodes >> Number_edges;
		vector<vector<pair<int, int> > > adj_list(Number_nodes, vector<pair<int, int> >());

		int a, b, c;

		for (int i = 0; i < Number_edges; i++)
		{
			cin >> a >> b >> c;
			adj_list[a].push_back({ b, c });
			adj_list[b].push_back({ a, c });


		}

		for (int i = 0; i < Number_nodes; i++)
		{
			double result = (double(Number_nodes - 1) / shortest_distance(i, adj_list));
			cout << setprecision(12)<< result << endl;
		}



	
	

	
	return 0;
}








int shortest_distance(int src,
	vector<vector<pair<int, int> > > & adj_list) {

	// Create queue
	priority_queue<pair<int, pair<int, int> >,
		vector<pair<int, pair<int, int>> >,
		greater<pair<int, pair<int, int> > > >nodes_q;

	// Create d and p arrays
	int n = adj_list.size();
	vector<int> d(n, INF);
	vector<int> p(n, -1);

	nodes_q.push({ 0, {src, src} });

	while (!nodes_q.empty()) {
		pair<int, pair<int, int> > cur_p = nodes_q.top();
		nodes_q.pop();
		int cur_node = cur_p.second.first;
		int cur_prev_node = cur_p.second.second;
		int cur_dis = cur_p.first;

		if (d[cur_node] != INF)
			continue;

		d[cur_node] = cur_dis;
		p[cur_node] = cur_prev_node;

		// Add the nodes connected to current one
		for (int i = 0;
			i < adj_list[cur_node].size();
			i++)
		{
			int next_node = adj_list[cur_node][i].first;
			int weight = adj_list[cur_node][i].second;
			if (d[next_node] != INF)
				continue;
			nodes_q.push({ cur_dis + weight,
						  {next_node, cur_node} });
		}
	}
	int result = 0;
	for (int i = 0; i < d.size(); i++)
	{
		result += d[i];
	}
	return result;
}