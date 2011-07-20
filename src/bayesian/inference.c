/* inference.c
   
   The inference algorithm used is Pearl's message-passing algorithm
   for DAG with a rooted-tree topology. (I am working on extending 
   the algorithm for singly-connected networks, aka polytrees).
   This algorithm is exact, and it's computationally intensive in 
   nature (NP-hard), depending on the topology and number of nodes.

   Copyright 2011.
   Authors:  Siddharth Kothari
   Project email: <tuxmath-devel@lists.sourceforge.net>
   Project website: http://tux4kids.alioth.debian.org

inference.c is part of "Tux, of Math Command", a.k.a. "tuxmath".

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
#include "inference.h"


/* local function prototypes */
void send_lambda_message(Bayesian_Network, int, int);
void send_pi_message(Bayesian_Network, int, int);


/* One-time initialization call before using the   */
/* update_tree function. Initializes the Evidence- */
/* set, and posterior probability is set to prior  */
/* probability, intialize lambda, pi message       */
/* @Param Bayesian_Network reference               */
void initial_tree(Bayesian_Network BN) {
  int i,j,node;   // counters
  int parent_index, root_in;
  link child;
  BN->E->count=0;                                // Initialize number of evidence nodes

  for (i = 0; i < BN->G->V; i++) {
    for (j = 0; j < NODE_VALUES; j++) { 
      BN->P[i]->lambda_value[j] = 1.0;           // Compute 'lambda' values
    }
    for (j = 0; j < NODE_VALUES; j++)
      BN->P[i]->lambda_message[j] = 1.0;         // Compute 'lambda' messages
  }

  root_in = root_index(BN->G);


  for (j = 0; j < NODE_VALUES; j++) {
    BN->P[root_in]->pi_value[j] = BN->P[root_in]->probability[j];// Compute Root's 'pi' values
  }
   
  child = child_reference(BN->G, root_in);
  for (; child != NULL; child=next_reference(child))       // Each child of 'Root'
    send_pi_message(BN, root_in, link_index(child));
}

/* Each time a (variable) Node is updated for a    */
/* 0/1, update_tree is called for finding out the  */
/* posterior probability of all the nodes.         */
/* @Param Bayesian_Network reference               */
/* @Param int node_index - The index of the insta  */
/* ntiated node.                                   */
/* @Param int node_value - The value(either 0 or 1)*/
void update_tree(Bayesian_Network BN, int node_index, int value) {
  int i, p_index;
  link child_list;

  if (ismember_Evidence_Set(BN, node_index) == -1) {
    BN->E->index[BN->E->count] = node_index;
    BN->E->count++;
  }
  for (i = 0; i < NODE_VALUES; i++) {
    if (i == value) {
      BN->P[node_index]->lambda_value[i] = 1.0;
      BN->P[node_index]->pi_value[i] = 1.0;
      BN->P[node_index]->post_probabilitiy[i] = 1.0;
    }
    else {
      BN->P[node_index]->lambda_value[i] = 0.0; 
      BN->P[node_index]->pi_value[i] = 0.0;
      BN->P[node_index]->post_probabilitiy[i] = 0.0;
    }
  }

  p_index = parent_index(BN->G, node_index);
  if (root_index(BN->G) != node_index && ismember_Evidence_Set(BN, p_index) == -1)
    send_lambda_message(BN, node_index, p_index);

  child_list = child_reference(BN->G, node_index);
  for(; child_list != NULL; child_list = next_reference(child_list)) {
    i = link_index(child_list);
    if (ismember_Evidence_Set(BN, i) == -1)
      send_pi_message(BN, node_index, i);
  }
}


void send_lambda_message(Bayesian_Network BN, int node_child, int node_parent) {
  int i,j;
  double temp = 0.0;
  double normalizer;
  link child_list;

  for (i = 0; i < NODE_VALUES; i++) {
    for (temp = 0.0, j = 0; j < NODE_VALUES; j++)
      temp += BN->P[node_child]->probability[2*i+j]*BN->P[node_child]->lambda_value[j];
    BN->P[node_child]->lambda_message[i] = temp;

    temp = 1.0;
    child_list = child_reference(BN->G, node_parent);
    for (; child_list != NULL; child_list = next_reference(child_list)) {
      j = link_index(child_list);
      temp *= BN->P[j]->lambda_message[i];
    }
    BN->P[node_parent]->lambda_value[i] = temp;

    BN->P[node_parent]->post_probabilitiy[i] = BN->P[node_parent]->lambda_value[i]*BN->P[node_parent]->pi_value[i];
  }
  // normalize the probabilities
  normalizer = 1.0/(BN->P[node_parent]->post_probabilitiy[0] + BN->P[node_parent]->post_probabilitiy[1]);
  for (i = 0; i < NODE_VALUES; i++)
    BN->P[node_parent]->post_probabilitiy[i] *= normalizer;

  i = parent_index(BN->G, node_parent);
  if (root_index(BN->G) != node_parent && ismember_Evidence_Set(BN, i) == -1)
    send_lambda_message(BN, node_parent, i);

  
  child_list = child_reference(BN->G, node_parent);
  for (; child_list != NULL; child_list = next_reference(child_list)) {
    i = link_index(child_list);
    if (i != node_child && ismember_Evidence_Set(BN, i) == -1)
      send_pi_message(BN, node_parent, i);
  }
}


void send_pi_message(Bayesian_Network BN, int node_parent, int node_child) {
  int i, j, index;              // counters and temporary storage variables
  link children_list; 
  double temp = 0.0;
  double normalizer;
  printf("node: %d\n", node_child);
  for (i = 0; i < NODE_VALUES; i++) {
    temp = BN->P[node_parent]->pi_value[i];
    if (node_child == 3)
      printf("tmep -> %.4lf\n", temp);
    children_list = child_reference(BN->G, node_parent);
    for (; children_list != NULL; children_list = next_reference(children_list)) {
      index = link_index(children_list);
      if (index != node_child)
        temp *= BN->P[index]->lambda_message[i];
    }
    BN->P[node_child]->pi_message[i] = temp; 
  }

  for (i = 0; i < NODE_VALUES; i++) {
    for (j = 0, temp = 0.0; j < NODE_VALUES; j++)
      temp += (BN->P[node_child]->probability[i+2*j])*(BN->P[node_child]->pi_message[j]);
    BN->P[node_child]->pi_value[i] = temp;
    BN->P[node_child]->post_probabilitiy[i] = BN->P[node_child]->lambda_value[i]*BN->P[node_child]->pi_value[i];
  }
 
  normalizer = 1.0/(BN->P[node_child]->post_probabilitiy[0]+BN->P[node_child]->post_probabilitiy[1]);
  for (i = 0; i < NODE_VALUES; i++)
    BN->P[node_child]->post_probabilitiy[i] *= normalizer;

  children_list = child_reference(BN->G, node_child);
  for(; children_list != NULL; children_list = next_reference(children_list)) {
    index = link_index(children_list);
    if (ismember_Evidence_Set(BN, index) == -1)
      send_pi_message(BN, node_child, index);
  }
}
