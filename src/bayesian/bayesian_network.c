/* bayesian_network.c
  
   This is the main Bayesian_network file. Contains all the functions
   for constructing and inferencing.
   
   Copyright 2005, 2008, 2009, 2010.
   Authors:  Siddharth Kothari
   Project email: <tuxmath-devel@lists.sourceforge.net>
   Project website: http://tux4kids.alioth.debian.org

bayesian_network.c is part of "Tux, of Math Command", a.k.a. "tuxmath".

Tuxmath is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

Tuxmath is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.  
*/

#include <stdio.h>
#include <stdlib.h>
#include "bayesian_network.h"


/* Initializes a Bayesian network with a specified */
/* number of nodes.                                */
/* @Param int - Number of nodes in the Bayesian    */
/* network                                         */
Bayesian_Network BN_init(int total_nodes) {
  int i = 0;
  Bayesian_Network BN = malloc(sizeof *BN);
  BN->G = graph_init(total_nodes);
  BN->P = malloc(total_nodes*sizeof(Joint_Probability));
  for (; i < total_nodes; i++)
    BN->P[i] = NULL;
  return BN;
}

/* Adds a link from a node to the other. The nodes */
/* are identified only by indices                  */
/* @Param Bayesian_Network instance                */
/* @Param int - The 'from' node index              */
/* @Param int - The 'to' node index                */
void BN_add_link(Bayesian_Network BN, int node1, int node2) {
  graph_insert_edge(BN->G, EDGE(node1, node2));
}

/* Removes an existing link between two nodes. The */
/* direction of the link is identified by the posi-*/
/* tion of the arguments.                          */
/* @Param Bayesian_Network instance                */
/* @Param int - The 'from' node index              */
/* @Param int - The 'to' node index                */
void BN_remove_link(Bayesian_Network BN, int node1, int node2) {
  graph_remove_edge(BN->G, EDGE(node1, node2));
}

/* Specify the initial probabilites for each node  */
/* @Param Bayesian_Network instance                */
/* @Param int - the node index                     */
/* @Param double[] - the probability distribution  */
/* specified as an array(since the number of prob- */
/* abilities required depends on the number of     */
/* incoming links)                                 */
void BN_nodeprobability(Bayesian_Network BN, int node, double probability[]) {
  int num = get_number_parents(BN->G, node);
  int index = 0;
  num = 1<<num;
  BN->P[node] = malloc(sizeof(Joint_Probability));
  BN->P[node]->number = num;
  BN->P[node]->probability = (double *)malloc(num*sizeof(double));
  for (; index < num; index++) {
    BN->P[node]->probability[index] = probability[index];
  }
}

/* Prints on the console the relations among nodes */
/* and the probability distribution                */
/* @Param Bayesian_Network instance                */
void BN_display(Bayesian_Network BN) {
  printf("Structure\n");
  graph_display(BN->G);
  printf("Joint probability distribution\n");
  int v = 0, i;
  Joint_Probability p;
  Graph g = BN->G;
  for (; v < g->V; v++) {
    printf("Node #%d: ", v);
    for (i = 0; i < BN->P[v]->number; i++)
      printf("%.2lf, ", BN->P[v]->probability[i]);
    printf("\n");
  }
}
