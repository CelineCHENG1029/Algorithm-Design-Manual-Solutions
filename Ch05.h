#pragma once
#include <iostream>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;

class Graph {
private:
	enum Color { white, black, uncolored };
public:
	class edgeNode;

	static const int MAXV = 1000;
	int nvertex;
	int nedges;
	bool directed;	
	edgeNode* edges[MAXV + 1]; /* adjacency info */
	int degrees[MAXV + 1]; /* outdegree of each vertex */

	bool discovered[MAXV + 1];
	bool processed[MAXV + 1];
	int parent[MAXV + 1];

	Color color[MAXV + 1];
	bool bipartite;

	Graph();
	void read_graph();
	void read_graph_from_file(string file_path);
	void insert_edge(int x, int y, bool single);
	void print_graph();

	void initialize_search();
	void breathFirstTraverse(int start_vertex);
	void pre_process_vtx(int vtx);
	void process_edge(int vtx, int adjvtx);
	void post_process_vtx(int vtx);
	void find_path(int start, int end);

	int count_connected_components();
	bool check_two_color();
	Color complementary_color(Color color);
};

class Graph::edgeNode {
public:
	int adjv;
	int weight;
	edgeNode* next;

	edgeNode(int adjv, int weight, edgeNode* next);
};