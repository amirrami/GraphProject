#include <vector>
#include <cctype>
#include <cstdlib>
#include<map>

#include <iostream>
#include<fstream>

using namespace std;

int main()
{
	
	int Number_nodes, Number_edges;
	ifstream my_file("example.txt");
	if (my_file.is_open())
	{
		my_file >> Number_nodes >> Number_edges;
		vector<vector<pair<int, int> > > adj_list(Number_nodes, vector<pair<int, int> >());
		
		int a, b, c;

		for (int i = 0; i < Number_edges; i++)
		{
			my_file >> a >> b >> c;
			adj_list[a].push_back({ b, c });
			adj_list[b].push_back({ a, c });


		}

		for (int i = 0; i < Number_nodes; i++)
		{
			cout <<adj_list[i].size() <<endl ;

		}

	
	

	}
	else
		cout << "file not opened" << endl;

	my_file.close();
	//system("pause");
	return 0;
}