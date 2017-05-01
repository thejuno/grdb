#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void cst_graph_init(cst_graph_t cst_g) {
	assert (cst_g != NULL);
	memset(g, 0, sizeof(struct cst_graph));
}

vertex_t cst_find_source_node(graph_t g) {
	vertex_t v;
	
	assert (g != NULL);
	
	v = g->v;
	
	return v;
}

bool check_tuple(edge_t e_start, edge_t e_next) {
	attribute_t attr;
	tuble_t t;

	for (attr = t->s->attrlist; attr != NULL; attr = attr->next) {
		if (attr->bt == CHARACTER || attr->bt == VARCHAR || attr->bt == BOOLEAN || attr->bt == ENUM) {
			if (e_start->tuple->buf == e_next->tuple->buf)
				return 1;
			else
				return 0;
		}	
	}
}

vertex_t cst_find_neighbor_node(vertex_t v, graph_t g) {
	edge_t e;
	edge_t e_next;
	vertex_t w;
	vertexid_t id;
	
	assert (v != NULL);
	assert (g != NULL);
	
	// checking if v_start is equal to the vertex with the first ID
	if (v == g->v) {
		w->neighbor = v->next;
		return w->neighbor;
	}
	else {
		// initial edge for cst graph
		e = g->e;
		e_next = g->e->next;
		// finding next vertex for cst graph by comparing tuples of previous edge and next edge 
		for (e = e_next; e != NULL; e = e_next->next) {
			// When there are multiple edges with the same tuple that can choose from, we choose the edge that comes first in the order
			if (check_tuple(e, e_next)) {
				id = e_next->id2;
				v->id = id;
				w->neighbor = v;
				return w->neighbor;
			}
		}	
	}
	// no neighbor node == no common schema	
	return NULL:
}

void remove_edge(graph_t g, edge_t e) {
	if (g->e == e)
		free(g->e);
	memset(e, 0, sizeof(struct edge));
}

void remove_vertex(graph_t g) {
	vertex_t v;
	edge_t e;

	for (v = g->v; v!= NULL; v = v->next) {
		for (e = g->e; e != NULL; e = e->next) {
			if (v->id == e->id1 || v->id == e->id2)
				return;
			else
				free(v);
			memset(v, 0, sizeof(struct vertex));
		}
	}
}

void cst_graph_complete_vertex(cst_graph_t g, vertex_t v) {
	vertex_t w;

	assert (g != NULL);
	assert (v != NULL);

	if (g->v == NULL) {
		/* Insert vertex into empty graph */
		g->v = v;
		return;
	}
	/* Insert at the end of the double linked list */
	for (w = g->v; w->next != NULL; w = w->next);
	w->next = v;
	v->prev = w;
}

void cst_graph_complete_edge(cst_graph_t g, edge_t e) {
	edge_t f;
	
	assert (g != NULL);
	assert (e != NULL);
	
	if (g->e == NULL) {
		/* Insert edge into empty graph */
		g->e = e;
		return;
	}
	/* Insert at the end of the double linked list */
	for (f = g->e; f->next != NULL; f = f->next);
	f->next = e;
	e->prev = f;
} 

void cst_grow(vertex_t v, graph_t g) {
	vertex_t w;
	edge_t e;
	cst_graph_t cst_g;

	w = (vertex_t) malloc(sizeof(struct vertex));
	e = (edge_t) malloc(sizeof(struct edge));	

	w = cst_find_neighbor_node(v, g);
	// no next edge available
	if (w == NULL)
		return;

	// adding neighbor vertex to cst graph vertex	
	cst_graph_complete_vertex(cst_g, w);

	// adding edge between source vertex and neighbor vertex
	e = graph_find_edge_by_ids(g, v->id, w->id);
	cst_graph_complete_edge(cst_g, e);
	remove_edge(g, e);
	remove_vertex(g);
	
	// grow cst graphs
	cst_grow(w,g);
}

void cst_graph_insert(cst_graph_t cst_g) {
	cst_graph_t cst_f;

	if (graphs == NULL) {
		// when a set of cst graphs is empty, insert first cst_g
		graphs = cst_g;
		return;
	}
	// inserting additional cst graphs to the set of cst graphs
	for (cst_f = cst_graphs; cst_f != NULL; cst_f = cst_f->next);
	cst_f->next = cst_g;
}

void cst_sets_graph(graph_t g) {
	cst_graph_t cst_g;

	// Build cst graphs until the general graph gets empty
	while (g != NULL) {
		v->start = cst_find_source_node(g);

		// insert the source vertex to cst graph	
		cst_graph_complete_vertex(cst_g, v->start);

		// grow cst graphs
		cst_grow(cst_find_neighbor_node(v->start, g), g);

		// adding cst graphs one by one
		cst_graph_insert(cst_g);
	}	
}
