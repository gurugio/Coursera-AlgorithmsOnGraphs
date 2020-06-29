#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

using std::vector;
using std::pair;
using namespace std;

double get_distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

int find_group(vector<int>* groups, int groups_size, int point_num)
{
	for (int i = 0; i < groups_size; i++) {
		if (groups[i].size() > 0) {
			for (int j = 0; j < groups[i].size(); j++) {
				if (groups[i][j] == point_num)
					return i;
			}
		}
	}
	return -1;
}

double minimum_distance(vector<int> x, vector<int> y) {
	double result = 0.;
	//write your code here

	int num_points = x.size();
	
	// each edge: <length, <start-point, end-point>>
	// priority_queue finds the shortest edge
	priority_queue<pair<double, pair<int, int>>,
				   vector<pair<double, pair<int, int>>>,
				   greater<pair<double, pair<int, int>>>> edge_queue;
	vector<int> groups[num_points];
	
	for (int i = 0; i < num_points - 1; i++) {
		for (int j = i+1; j < num_points; j++) {
			// push distance, #start-node, #end-node
			edge_queue.push(make_pair(get_distance(x[i], y[i], x[j], y[j]), make_pair(i, j)));
		}						   
	}

	for (int i = 0; i < num_points; i++)
		groups[i].push_back(i);

	for (int i = 0; i < num_points; i++) {
		if (groups[i].size() > 0) {
			cout << "group" << i << ":";
			for (int j = 0; j < groups[i].size(); j++) {
				cout << groups[i][j] << " ";
			}
			cout << endl;
		} else {
			cout << "group" << i << ": empty\n";
		}
	}

	while (!edge_queue.empty()) {
		double len = edge_queue.top().first;
		int s = edge_queue.top().second.first;
		int e = edge_queue.top().second.second;
		edge_queue.pop();

		cout << "minimum edge: " << len << " " << s << "->" << e << endl;

		int sgroup = find_group(groups, num_points, s);
		int egroup = find_group(groups, num_points, e);
		cout << "group:" << sgroup << ":" << egroup << endl;
		
		if (sgroup == egroup) {
			cout << "same group: ignore\n";
			continue;
		} else {
			// move all from group[e] to group[s]
			while (groups[egroup].size() > 0) {
				int t = groups[egroup].back();
				groups[egroup].pop_back();
				groups[sgroup].push_back(t);
			}
			result += len;
		}

		// debugging
		for (int i = 0; i < num_points; i++) {
			cout << "group" << i << ":";
			for (int j = 0; j < groups[i].size(); j++) {
				cout << groups[i][j] << " ";
			}
			cout << endl;
		}
	}
	
	return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
