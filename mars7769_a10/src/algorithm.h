/*
--------------------------------------------------
Project: a10q3
File:    algorithm.h
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "edgelist.h"
#include "graph.h"

EDGELIST *mst_prim(GRAPH *g, int start);
EDGELIST *spt_dijkstra(GRAPH *g, int start);
EDGELIST *sp_dijkstra(GRAPH *g, int start, int end);

#endif
