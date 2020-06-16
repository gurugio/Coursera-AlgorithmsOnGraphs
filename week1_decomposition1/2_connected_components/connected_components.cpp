#include <iostream>
#include <vector>

using namespace std;
using std::vector;
using std::pair;


void explore(vector<vector<int> > &adj, bool* visited, int current)
{
	visited[current] = true;
	//cout << "VIsiT: " << current << endl;
	for (const int& i : adj[current]) {
		if (visited[i] == false)
			explore(adj, visited, i);
	}
}


int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  //write your code here

  bool* visited = new bool[adj.size()];

  for (int i = 0; i < adj.size(); i++)
	  visited[i] = false;

  for (int i = 0; i < adj.size(); i++) {
	  if (visited[i] == false) {
		  res++;
		  explore(adj, visited, i);
	  }
  }
  
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
