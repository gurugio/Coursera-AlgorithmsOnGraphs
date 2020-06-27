#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using namespace std;




int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
	//write your code her

	// pair<sum of weight, node number>
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_queue;
	vector<int> dist(adj.size(), 0xffffff);
	vector<int> visit(adj.size(), 0);

	cout << s << "->" << t << endl;
	visit[s] = 1;
	min_queue.push(make_pair(0, s)); // pair(weight, node#)
	dist[0] = 0;

	while (!min_queue.empty()) {
		pair<int, int> min = min_queue.top();
		min_queue.pop();

		int weight =  min.first;
		int node =  min.second;

		cout << "curren-node: " << node << " weight:" << weight << endl;

		for (int i = 0; i < adj[node].size(); i++) { // scan all nodes that are visible from current node
			int scan_node = adj[node][i];
			if (visit[scan_node] == 0 || (dist[scan_node] > weight + cost[node][i])) {
				visit[scan_node] = 1;
				dist[scan_node] = weight + cost[node][i];

				cout << "new minimum: " << scan_node << " weight: " << dist[scan_node] << endl;
				min_queue.push(make_pair(dist[scan_node], scan_node));
			}
		}
	}
	
	return dist[t] == 0xffffff ? -1 : dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
