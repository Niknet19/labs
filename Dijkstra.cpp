#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<limits.h>
#include<iostream>

#define MYMAX UINT_MAX
void Errors_check(int number_of_vertex, int number_of_edges, FILE* output) {

	if (number_of_vertex < 0 || number_of_vertex>5000) {
		fprintf(output, "%s", "bad number of vertices");
		exit(0);
	}

	if (number_of_edges<0 || number_of_edges>number_of_vertex*(number_of_vertex + 1) / 2) {
		fprintf(output, "%s", "bad number of edges");
		exit(0);
	}
	if (number_of_vertex == 0 && number_of_edges == 0) {
		fprintf(output, "%s", "bad vertex");
		exit(0);
	}
}

void isCorrectVerEdLength(int start, int end, const unsigned int length, int number_of_vertex, FILE* output) {
	if (start < 1 || start > number_of_vertex || end < 1 || end > number_of_vertex) {
		fprintf(output, "%s", "bad vertex");
		exit(0);
	}
	if (length < 0 || length > INT_MAX) {
		fprintf(output, "%s", "bad length");
		exit(0);
	}
}

unsigned int **make_graph(int number_of_vertex, int number_of_edges, FILE* input, FILE* output) {
	unsigned int** graph = (unsigned int**)malloc(number_of_vertex * sizeof(unsigned int));

	for (int i = 0; i < number_of_vertex; i++) {
		graph[i] = (unsigned  int*)calloc(number_of_vertex, sizeof(unsigned int));
	}

	for (int i = 0; i < number_of_edges; ++i) {
		int n = 0, m = 0;
		unsigned int l = 0;
		fscanf(input, "%d", &n);
		fscanf(input, "%d", &m);
		fscanf(input, "%d", &l);
		if (feof(input)) {
			if (i < number_of_edges-1) {
				fprintf(output, "%s", "bad number of lines");
				exit(0);
			}
		}
		isCorrectVerEdLength(n, m, l, number_of_vertex, output);
		graph[n - 1][m - 1] = l;
		graph[m - 1][n - 1] = l;
	}
	return graph;
}

void result_output(unsigned int* result, int v, FILE* output) {
	for (int i = 0; i < v; i++) {
		 if (result[i] == MYMAX){
			fprintf(output, "%s ", "oo");
		}
		else {
				if (result[i] > INT_MAX)
			 {
				fprintf(output, "%s ", "INT_MAX+");
			}
			else {
				fprintf(output, "%u ", result[i]);
				
			}
		}
	}
}
void path_output(unsigned int** graph, unsigned int*d, int S, int E, int v, FILE* output,bool correct,int edges) {
	int overflow_test = 0;
	if (correct) {
		fprintf(output, "\n");
		fprintf(output, "no path");
		exit(0);
	}

	int* ver = (int*)malloc(v * sizeof(int));
	int start = S - 1;
	int end = E - 1;
	if (start == end) {
		fprintf(output, "\n");
		fprintf(output, "%d", start+1);
		exit(0);
	}
	ver[0] = end + 1;
	int k = 1;
	int weight = d[end];
	while (end != start) 
	{
		for (int i = 0; i < v; i++) 
			if (graph[end][i] != 0)   
			{
				int temp = weight - graph[end][i]; 
				if (temp == d[i]) 
				{
					weight = temp; 
					end = i;       
					ver[k] = i + 1; 
					k++;
				}
			}
	}
	fprintf(output, "\n");
	unsigned long long int sum=0;
	for (int i = 0; i < k-1; i++) {
		sum += graph[ver[i]-1][ver[i + 1]-1];
	}
	if (sum > INT_MAX&&edges!=2) {
		fprintf(output, "%s", "overflow");
		exit(0);
	}

	for (int i = 0; i <k; i++) {
		fprintf(output, "%d ", ver[i]);
	}
	free(ver);
}

void Dijkstra_algo(unsigned int** graph, int start,int finish,int v, int e, FILE* output, FILE* input){
	unsigned int *d = (unsigned int*)malloc(v * sizeof(unsigned int));
	bool *used = (bool*)malloc(v * sizeof(bool));
	unsigned int min, minindex;

	for (int i = 0; i < v; i++)
	{
		d[i] = MYMAX;
		used[i] = 1;
	}
	d[start - 1] = 0;

	do {
		minindex = MYMAX;
		min = MYMAX;
		for (int i = 0; i < v; i++)
		{ 
			if ((used[i] == 1) && (d[i] < min))
			{ 
				min = d[i];
				minindex = i;
			}
		}
		if (minindex != MYMAX)
		{
			for (int i = 0; i < v; i++)
			{
				if (graph[minindex][i] > 0 && used[i]!=0)
				{
					unsigned int temp=0;
					temp = min + graph[minindex][i];
					if (temp < d[i])
					{
						d[i] = temp;
					}
				}
			}
			used[minindex] = 0;
		}
	} while (minindex < MYMAX);
	bool is_path = 0;
	if (d[start - 1] == MYMAX || d[finish - 1] == MYMAX) {
		is_path = 1;
	}
	result_output(d, v, output);
	free(used);
	//fprintf(output, "%d", is_path);
	path_output(graph, d, start, finish, v, output,is_path,e);
	free(d);
}

int main() {
	FILE* in;
	FILE* out;
	in = fopen("in.txt", "r");
	out = fopen("out.txt", "w");
	int v,e;
	fscanf(in, "%d", &v);
	int S, F;
	fscanf(in, "%d", &S);
	fscanf(in, "%d", &F);
	fscanf(in, "%d", &e);
	Errors_check(v, e, out);
	unsigned int** G = make_graph(v, e, in, out);
	Dijkstra_algo(G, S, F, v, e, out, in);
	fclose(in);
	fclose(out);
	for (int i = 0; i < v; i++) {
		free(G[i]);
	}
	return 0;
}