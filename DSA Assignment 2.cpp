#include "tree.hpp"

int main(){

	BST<int> t;
	
	// t.add_vertex("A", 1);
	// t.add_vertex("B", 3);
	// t.add_vertex("C", 5);
	// t.add_vertex("D", 10);
	// t.add_vertex("G", 20);
	// t.add_vertex("E", 15);
	// t.add_vertex("H", 30);
	// t.add_vertex("F", 17);

	// t.add_vertex("M", 1);
	// t.add_vertex("G", 1);
	// t.add_vertex("S", 1);
	// t.add_vertex("H", 1);
	// t.add_vertex("R", 1);
	// t.add_vertex("Z", 1);
	// t.add_vertex("A", 1);

	t.add_vertex("C", 5);
	t.add_vertex("A", 1);
	t.add_vertex("H", 10);
	t.add_vertex("D", 3);
	t.add_vertex("G", 20);
	t.add_vertex("F", 15);
	t.add_vertex("B", 30);
	t.add_vertex("E", 17);

	t.remove_vertex("F");

	cout << boolalpha;

	cout << "Number of Vertices: " << t.num_vertices() << "\n";
	cout << "Number of Edges: " << t.num_edges() << "\n";
	cout << "Sum weight: " << t.sum_weight() << "\n";
	// cout << "Degree of E: " << t.degree("E") << "\n";
	cout << "Vertices:\n";
	for(auto& v : t.get_vertices()) {
		cout << v << ' ';
	}
	cout << "\n";
	cout << "Leaves:\n";
	for (auto& v : t.get_leaves()){
		cout << v << ' ';
	}
	cout << "\n";
	cout << "is adjacent: " << t.adjacent("G", "D") << "\n";

	cout << "Path: ";
	vector<string> path = t.path("D", "E");
	for(int i = 0; i < path.size(); ++i) {
		cout << path[i] << ' ';
	}
	cout << "\n";

	cout << "Path with largest weight: ";
	for(auto x : t.path_with_largest_weight()){
		cout << x << " ";
	}
	cout << endl;

	cout << "Height: " << t.height() << "\n";

	// cout << t.num_vertices() << endl;
	// cout << t.num_edges() << endl;

	// cout << t.sum_weight() << endl;
	
	
}
