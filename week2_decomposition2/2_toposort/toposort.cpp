#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;
using namespace std;


// run dfs once and add visited nodes reversely
void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
	//write your code here

	used[x] = 1;
	
	for (int i: adj[x]) {
		if (used[i] == 0)
			dfs(adj, used, order, i);
	}

	// When it is already visited (pre-order), add it to the order.
	order.push_back(x);
}     

vector<int> toposort(vector<vector<int> > adj) {
	vector<int> used(adj.size(), 0);
	vector<int> order;
	//write your code here

	for (int i = 0; i < adj.size(); i++) {
		if (used[i] == 0)
			dfs(adj, used, order, i);
	}
	return order;
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

	for (size_t i = 0; i < n; i++)
		if (!adj[i].empty())
			cout << i << "-" << adj[i][0] << endl;
	
	vector<int> order = toposort(adj);
	for (size_t i = 0; i < order.size(); i++) {
		std::cout << order[i] + 1 << " ";
	}
}
