#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;
using namespace std;


#if 0
//
// first solution(slow): run DFS for all nodes
//

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
	//write your code here
	used[x] = 1;
	cout << "visit: " << x << endl;

	// if no out-edge, remove it from adj and append it to order
	if (adj[x].empty()) {
		cout << "add order: " << x << endl;
		order.push_back(x);

		for (int i = 0; i < adj.size(); i++) {
			if (!adj[i].empty() && adj[i][0] == x) {
				adj[i].pop_back();
			}
		}
	} else if (used[adj[x][0]] == 0) {
			dfs(adj, used, order, adj[x][0]);
	}
}     

vector<int> toposort(vector<vector<int> > adj) {
	vector<int> used(adj.size(), 0);
	vector<int> order;
	//write your code here

	for (int i = 0; i < adj.size(); i++) {
		cout << "start dfs: " << i << endl;
		if (!adj[i].empty())
			dfs(adj, used, order, i);

		// clear visited flag
		for (int j = 0; j < used.size(); j++)
			used[j] = 0;
	}

	// all nodes are disconnected now.
	// add remained nodes to order
	for (int i = 0; i < adj.size(); i++) {
		bool found = false;
		for (int j = 0; j < order.size(); j++) {
			if (i == order[j])
				found = true;
		}
		if (!found)
			order.push_back(i);
	}	
	
	return order;
}
#endif

// 2nd fast solution: run dfs once and add visited nodes reversely
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
