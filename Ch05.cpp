#include "stdafx.h"
#include "Ch05.h"


using namespace std;

Graph::edgeNode::edgeNode(int adjv, int weight, edgeNode* next): adjv(adjv), weight(weight), next(next) {
	
};

Graph::Graph(): nvertex(0), nedges(0), directed(false)
{
	for (int i = 1; i <= MAXV; ++i) {
		edges[i] = nullptr;
		degrees[i] = 0;
	}
}

void Graph::read_graph_from_file(string file_path) {
	string line;
	ifstream file;
	file.open(file_path);

	int nline = 0;
	int idx = 0;
	int x = 0, y = 0;

	while (!file.eof()) {
		switch (nline)
		{
		case 0:			
			file >> idx;
			directed = idx ? true : false;
			++nline;
			break;	
		case 1:
			file >> nvertex >> nedges;
			++nline;
			break;
		default:			
			file >> x >> y;
			insert_edge(x, y, true);
		}
	}
}

void Graph::read_graph() {

	int idx = 0;
	cout << "Directed graph or not (1/0): ";
	cin >> idx;
	directed = idx ? true : false;

	int ne = 0;
	cout << "Input number of vertexes and edges: ";
	cin >> nvertex >> ne;

	cout << "Input edge pairs: " << endl;
	int x = 0, y = 0;
	for (int i = 1; i <= ne; ++i) {
		cin >> x >> y;
		insert_edge(x, y, true);
	}
}

void Graph::insert_edge(int x, int y, bool single) {
	edgeNode* cur = new edgeNode(y, 0, nullptr);
	cur->next = edges[x];

	edges[x] = cur;
	++degrees[x];

	if (directed) {
		++nedges;
	}
	else {
		if (single) {
			insert_edge(y, x, !single);
		}
		else {
			++nedges;
		}
	}
}

void Graph::print_graph() {
	for (int i = 1; i <= nvertex; ++i) {
		cout << "Vertex " << i << ": ";
		edgeNode* p = edges[i];
		while (p) {
			cout << p->adjv << ' ';
			p = p->next;
		}
		cout << endl;
	}
}

void Graph::initialize_search() {
	for (int i = 1; i <= nvertex; ++i) {
		discovered[i] = false;
		processed[i] = false;
		parent[i] = -1;
	}
}

void Graph::breathFirstTraverse(int start_vertex) {
	queue<int> q;
	q.push(start_vertex);
	
	discovered[start_vertex] = true;
	edgeNode* node = nullptr;
	int vtx, adjvtx = 0;

	while (!q.empty()) {
		vtx = q.front();
		q.pop();
		// pre_process_vtx(vtx); /* general case */
		processed[vtx] = true;		
		node = edges[vtx];

		while (node) {
			adjvtx = node->adjv;
			if (!processed[adjvtx] || directed) {
				process_edge(vtx, adjvtx);
			}
			if (!discovered[adjvtx]) {
				discovered[adjvtx] = true;
				q.push(adjvtx);
				parent[adjvtx] = vtx;
			}
			node = node->next;
		}
	}
}

void Graph::pre_process_vtx(int vtx) {
	cout << "process Vertex " << vtx << ':' << endl;
}

void Graph::process_edge(int vtx, int adjvtx) {
	// cout << "edge: " << vtx << '-' << adjvtx << endl; /* general case */
	
	// check_two_color
	if (color[vtx] == color[adjvtx]) {
		bipartite = false;
		cout << "Not bipartite due to edge (" << vtx << ',' << adjvtx << ')' << endl;
	}
	color[adjvtx] = complementary_color(color[vtx]);
}

void Graph::post_process_vtx(int vtx){}

void Graph::find_path(int start, int end) {
	if (start == end || end == -1) {
		cout << start << ' ';
	}
	else {
		find_path(start, parent[end]);
		cout << end << ' ';
	}

}

int Graph::count_connected_components() {
	int count = 0;
	for (int i = 1; i <= nvertex; ++i) {
		if (!discovered[i]) {
			breathFirstTraverse(i);
			++count;
		}
	}
	return count;
}

bool Graph::check_two_color() {

	bipartite = true;

	for (int i = 1; i <= nvertex; ++i) {
		color[i] = uncolored;
	}

	for (int i = 1; i <= nvertex; ++i) {
		if (!discovered[i]) {
			color[i] = white;
			breathFirstTraverse(i);
		}
	}
	return bipartite;
}

Graph::Color Graph::complementary_color(Color color) {
	if (color == white) return black;
	if (color == black) return white;

	return uncolored;
};