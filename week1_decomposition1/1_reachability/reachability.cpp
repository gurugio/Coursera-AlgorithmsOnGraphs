#include <iostream>
#include <vector>

using namespace std;
using std::vector;
using std::pair;


// 1 - 2
// 3 - 2
// 4 - 3
// 1 - 4


void explore(vector<vector<int> > &adj, bool* visited, int current)
{
	visited[current] = true;
	//cout << "VIsiT: " << current << endl;
	for (const int& i : adj[current]) {
		if (visited[i] == false)
			explore(adj, visited, i);
	}
}

int reach(vector<vector<int> > &adj, int x, int y) {
	int ret;
	bool* visited = new bool[adj.size()];
	explore(adj, visited, x);
	ret = visited[y];
	delete [] visited;
	return ret;
}

int main() {
	size_t n, m;
	// n: number of nodes
	// m: number of edges
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for (size_t i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		// no direction
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	
	int x, y;
	std::cin >> x >> y;
	std::cout << reach(adj, x - 1, y - 1);
}
