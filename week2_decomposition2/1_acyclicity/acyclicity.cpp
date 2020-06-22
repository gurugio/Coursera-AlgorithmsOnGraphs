#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
using std::vector;
using std::pair;


int explore_acyclic(vector<vector<int> >& adj, int* visited_color, int current)
{
	int ret = 1;
	visited_color[current] = 1;
	cout << "visit: " << (current+1) << endl;

	for (const int& i: adj[current]) {
		cout << "check: " << (current+1) << "->" << (i+1) << endl;
		if (visited_color[i] == 0) {
			if (explore_acyclic(adj, visited_color, i) == 0)
				return 1; // found cycle
		} else if (visited_color[i] == 1) { // found back-edge
			cout << "back-edge: " << (current+1) << "->" << (i+1) << endl;
			return 1; // found cycle
		}
		//assert(visited_color[i] != 2);
	}
	visited_color[current] = 2; // black, finished
	cout << "finish: " << (current+1) << endl;
	return 0; // acyclic
}

int acyclic(vector<vector<int> > &adj) {
	// 0: white, not visited
	// 1: gray, discovered
	// 2: black, finished
	int* visited_color = new int[adj.size()];

	for (int i = 0; i < adj.size(); i++)
		visited_color[i] = 0;

	for (int i = 0; i < adj.size(); i++) {
		if (visited_color[i] == 0) {
			if (explore_acyclic(adj, visited_color, i) == 1)
				return 1; // found cycle
		}
	}
	
	return 0; // acyclic
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
