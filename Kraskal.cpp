#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<malloc.h>
#include<algorithm>
using namespace std;

void make_set(int v,short int* parent,short int* rank) {
	parent[v] = v;
	rank[v] = 0;
}

int find_set(int v, short int *parent, short int *rank) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set(parent[v], parent, rank);
}

void union_sets(int a, int b, short int* parent, short int* rank) {
	a = find_set(a, parent, rank);
	b = find_set(b, parent, rank);
	if (a != b) {
		if (rank[a] < rank[b])
			swap(a, b);
		parent[b] = a;
		if (rank[a] == rank[b])
			++rank[a];
	}
}


typedef struct edge {
	short int from, to;
	unsigned int w;
}edge;


int cmp(const void *a, const void *b) {
	edge *c = (edge*)a, *d = (edge*)b;
	return c->w - d->w;
}


void Errors_check(int number_of_vertex, int number_of_edges, FILE* output) {
	if (number_of_vertex == 0)
	{
		fprintf(output, "%s", "no spanning tree");
		exit(0);
	}


	if (number_of_vertex < 0 || number_of_vertex>5000) {
		fprintf(output, "%s", "bad number of vertices");
		exit(0);
	}


	if (number_of_edges<0 || number_of_edges>number_of_vertex*(number_of_vertex + 1) / 2) {
		fprintf(output, "%s", "bad number of edges");
		exit(0);
	}

	if (number_of_edges < number_of_vertex - 1) {
		fprintf(output, "%s", "no spanning tree");
		exit(0);
	}
}


void isCorrectVerEdLength(int start, int end, unsigned int length, int number_of_vertex, FILE* output) {
	if (start < 1 || start > number_of_vertex || end < 1 || end > number_of_vertex) {
		fprintf(output, "%s", "bad vertex");
		exit(0);
	}
	if (length < 0 || length > INT_MAX) {
		fprintf(output, "%s", "bad length");
		exit(0);
	}
}


edge* read_graph(FILE* in, FILE* out, const int v, const int e) {
	edge* edges_list;
	edges_list = (edge*)malloc(e * sizeof(edge));

	for (int i = 0; i < e; ++i) {
		short int n = 0, m = 0;
		unsigned int l = 0;

		fscanf(in, "%hi", &n);
		fscanf(in, "%hi", &m);
		fscanf(in, "%u", &l);
		if (feof(in)) {
			if (i < e) {
				fprintf(out, "%s", "bad number of lines");
				exit(0);
			}
		}
		isCorrectVerEdLength(n, m, l, v, out);
		n--;
		m--;

		edges_list[i].from = n;
		edges_list[i].to = m;
		edges_list[i].w = l;
	}
	return edges_list;
}


void Kruskal_algorithm(edge* graph, const int v, const int e, FILE* out) {
	short int* parent = (short int*)malloc(v * sizeof(short int));
	short int* rank = (short int*)calloc(v, sizeof(short int));
	edge* result;
	result=(edge*)malloc(e * sizeof(edge));
	qsort(graph, e, sizeof(edge), cmp);

	for (int i = 0; i < v; i++) {
		parent[i] = i;
	}
	int j = 0;
	int e_in_mst = 0;
	for (int i = 0; i < e; i++) {
		int a = graph[i].from;
		int b = graph[i].to;
		if (find_set(a, parent, rank) != find_set(b, parent, rank)) {
			union_sets(a, b, parent, rank);
			result[j].from = a + 1;
			result[j].to = b + 1;
			result[j].w = graph[i].w;
			j++;
			e_in_mst++;
		}
	}

	if (e_in_mst != v - 1) {
		fprintf(out,"%s", "no spanning tree");
		exit(0);
	}
	for (int i = 0; i < j; i++) {
		fprintf(out, "%d ", result[i].from);
		fprintf(out, "%d\n", result[i].to);
	}
	free(result);
	free(graph);
	free(parent);
	free(rank);
}

int main() {
	int v, e;
	FILE* in;
	FILE* out;
	in = fopen("in.txt", "r");
	out = fopen("out.txt", "w");
	fscanf(in, "%d", &v);
	fscanf(in, "%d", &e);
	Errors_check(v, e, out);
	Kruskal_algorithm(read_graph(in, out, v, e), v, e, out);
	fclose(in);
	fclose(out);
	return 0;
}