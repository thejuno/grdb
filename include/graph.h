#ifndef __GRAPH_H
#define __GRAPH_H


#include "schema.h"
#include "tuple.h"
#include "vertexid.h"


struct vertex {
	/* Every vertex has a unique vertex id */
	vertexid_t id;

	/* Links for vertex set data structure in memory */
	struct vertex *prev;
	struct vertex *next;
	struct vertex *start;
	struct vertex *neighbor;

	/* Vertex tuple */
	tuple_t tuple;
};

struct edge {
	/* Every edge has two vertex ids */
	vertexid_t id1, id2;

	/* Links for edge set data structure in memory */
	struct edge *prev;
	struct edge *next;

	/* Edge tuple */
	tuple_t tuple;
};

/* Genernal graph */
struct graph {
	struct vertex *v;	/* Vertices */
	schema_t sv;		/* Vertex schema */
	struct edge *e;		/* Edges */
	schema_t se;		/* Edge schema */
	enum_list_t el;		/* List of enums */

	struct graph *next;
};

/* Normal form graph */
struct cst_graph {
	struct vertext *v;	/* Vertices */
	schema_t sv;		/* Vertex schema */
	struct edge *e;		/* Edges */
	schema_t se;		/* Edge schema */
	enum_list_t el;		/* List of enums */

	struct cst_graph *next;
};

typedef struct vertex *vertex_t;
typedef struct edge *edge_t;
typedef struct graph *graph_t;
typedef struct cst_graph *cst_graph_t;

extern cst_graph_t cst_graphs;

void vertex_init(vertex_t v);
void vertex_set_id(vertex_t v, vertexid_t id);
void vertex_print(vertex_t v);

void edge_init(edge_t e);
void edge_set_vertices(edge_t e, vertexid_t id1, vertexid_t id2);
void edge_print(edge_t e);

void graph_init(graph_t g);
void graph_insert_vertex(graph_t g, vertex_t v);
vertex_t graph_find_vertex_by_id(graph_t g, vertexid_t id);
edge_t graph_find_edge_by_ids(graph_t g, vertexid_t id1, vertexid_t id2);
void graph_insert_edge(graph_t g, edge_t e);
void graph_print(graph_t g, int with_tuples);

/* Applying Dijkstra's algorithm to store user data */
void cst_graph_init(cst_graph_t cst_g);
vertex_t cst_find_source_node(graph_t g);
bool check_tuple(edge_t e_start, edge_t e_next);
vertex_t cst_find_neighbor_node(vertex_t v, graph_t g);
void cst_complete_edges(graph_t g);
void cst_complete_vertices(graph_t g);
void remove_edge(graph_t g, edge_t e);
void remove_vertex(graph_t g, vertex_t v);
void cst_graph_complete_vertex(cst_graph_t g, vertex_t v);
void cst_graph_complete_edge(cst_graph_t g, edge_t e);
void cst_grow(vertex_t v, graph_t g);
#endif
