/*
 * MaMaConstrFirst.h
 *
 *  Created on: Aug 5, 2012
 *      Author: vbonnici
 */
/*
Copyright (c) 2014 by Rosalba Giugno

This library contains portions of other open source products covered by separate
licenses. Please see the corresponding source files for specific terms.

RI is provided under the terms of The MIT License (MIT):

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MAMACONSTRFIRST_H_
#define MAMACONSTRFIRST_H_

#include "Graph.h"

namespace rilib{

class MaMaConstrFirst : public MatchingMachine{

public:

	MaMaConstrFirst(Graph& query) : MatchingMachine(query){

	}

	virtual void build(Graph& ssg){

		enum NodeFlag {NS_CORE, NS_CNEIGH, NS_UNV};
		NodeFlag* node_flags = new NodeFlag[nof_sn]; 						//indexed by node_id
		int** weights = new int*[nof_sn];									//indexed by node_id
		int* t_parent_node = (int*) calloc(nof_sn, sizeof(int));			//indexed by node_id
		MAMA_PARENTTYPE* t_parent_type = new MAMA_PARENTTYPE[nof_sn];		//indexed by node id

		for(int i=0; i<nof_sn; i++){
			node_flags[i] = NS_UNV;
			weights[i] = new int[3];
			weights[i][0] = 0;
			weights[i][1] = 0;
			//weights[i][2] = ssg.out_adj_sizes[i] + ssg.in_adj_sizes[i];
			weights[i][2] = ssg.out_adj_sizes[i] + ssg.in_adj_sizes[i];
			t_parent_node[i] = -1;
			t_parent_type[i] = PARENTTYPE_NULL;
		}




		int si = 0;
		int n;
		int nIT; int ni;
		int nnIT; int nni;
		int nqueueL = 0, nqueueR = 0;
		int maxi, maxv;
		int tmp;


		while(si < nof_sn){

			if(nqueueL == nqueueR){
				//if queue is empty....
				maxi = -1;
				maxv = -1;
				nIT = 0;
				while(nIT < nof_sn){
					if(node_flags[nIT]==NS_UNV &&  weights[nIT][2] > maxv){
						maxv = weights[nIT][2];
						maxi = nIT;
					}
					nIT++;
				}
				map_state_to_node[si] = maxi;
				map_node_to_state[maxi] = si;
				t_parent_type[maxi] = PARENTTYPE_NULL;
				t_parent_node[maxi] = -1;

				nqueueR++;

				n = maxi;
				nIT = 0;
				while(nIT < ssg.out_adj_sizes[n]){
					ni = ssg.out_adj_list[n][nIT];
					if(ni != n){
						weights[ni][1]++;
					}
					nIT++;
				}
				while(nIT < ssg.in_adj_sizes[n]){
					ni = ssg.in_adj_list[n][nIT];
					if(ni != n){
						weights[ni][1]++;
					}
					nIT++;
				}
			}


			if(nqueueL != nqueueR-1){
				maxi = nqueueL;
				for(int mi=maxi+1; mi<nqueueR; mi++){
					if(wcompare(map_state_to_node[mi], map_state_to_node[maxi], weights) < 0){
						maxi = mi;
					}
				}
				tmp = map_state_to_node[nqueueL];
				map_state_to_node[nqueueL] = map_state_to_node[maxi];
				map_state_to_node[maxi] = tmp;
			}

			n = map_state_to_node[si];
			map_node_to_state[n] = si;

			//move queue left limit
			nqueueL++;
			//update nodes' flags & weights
			node_flags[n] = NS_CORE;
			nIT = 0;
			while(nIT < ssg.out_adj_sizes[n]){
				ni = ssg.out_adj_list[n][nIT];
				if(ni != n){
					weights[ni][0]++;
					weights[ni][1]--;

					if(node_flags[ni] == NS_UNV){
						node_flags[ni] = NS_CNEIGH;
						t_parent_node[ni] = n;
//						if(nIT < ssg.out_adj_sizes[n])
							t_parent_type[ni] = PARENTTYPE_OUT;
//						else
//							t_parent_type[ni] = PARENTTYPE_IN;
						//add to queue
						map_state_to_node[nqueueR] = ni;
						map_node_to_state[ni] = nqueueR;
						nqueueR++;

						nnIT = 0;
						while(nnIT < ssg.out_adj_sizes[ni]){
							nni = ssg.out_adj_list[ni][nnIT];
							weights[nni][1]++;
							nnIT++;
						}
					}
				}
				nIT++;
			}

			nIT = 0;
			while(nIT < ssg.in_adj_sizes[n]){
				ni = ssg.in_adj_list[n][nIT];
				if(ni != n){
					weights[ni][0]++;
					weights[ni][1]--;

					if(node_flags[ni] == NS_UNV){
						node_flags[ni] = NS_CNEIGH;
						t_parent_node[ni] = n;
//						if(nIT < ssg.out_adj_sizes[n])
//							t_parent_type[ni] = PARENTTYPE_OUT;
//						else
							t_parent_type[ni] = PARENTTYPE_IN;
						//add to queue
						map_state_to_node[nqueueR] = ni;
						map_node_to_state[ni] = nqueueR;
						nqueueR++;

						nnIT = 0;
						while(nnIT < ssg.in_adj_sizes[ni]){
							nni = ssg.in_adj_list[ni][nnIT];
							weights[nni][1]++;
							nnIT++;
						}
					}
				}
				nIT++;
			}

			si++;
		}

		int e_count,o_e_count,i_e_count; int i;
		for(si = 0; si<nof_sn; si++){
			n = map_state_to_node[si];

			//nodes_attrs[si] = ssg.nodes_attrs[n];
			if(t_parent_node[n] != -1)
			parent_state[si] = map_node_to_state[t_parent_node[n]];
			else
				parent_state[si] = -1;
			parent_type[si] = t_parent_type[n];


			e_count = 0;
			o_e_count = 0;
			for(i=0; i<ssg.out_adj_sizes[n]; i++){
				if(map_node_to_state[ssg.out_adj_list[n][i]] < si){
					e_count++;
					o_e_count++;
				}
			}
			i_e_count = 0;
			for(i=0; i<ssg.in_adj_sizes[n]; i++){
				if(map_node_to_state[ssg.in_adj_list[n][i]] < si){
					e_count++;
					i_e_count++;
				}
			}

			edges_sizes[si] = e_count;
			o_edges_sizes[si] = o_e_count;
			i_edges_sizes[si] = i_e_count;

			edges[si] = new MaMaEdge[e_count];
			e_count = 0;
			for(i=0; i<ssg.out_adj_sizes[n];i++){
				if(map_node_to_state[ssg.out_adj_list[n][i]] < si){
					edges[si][e_count].source = map_node_to_state[n];
					edges[si][e_count].target = map_node_to_state[ssg.out_adj_list[n][i]];
					edges[si][e_count].attr = ssg.out_adj_attrs[n][i];
					e_count++;
				}
			}
//			for(i=0; i<ssg.in_adj_sizes[n];i++){
//				if(map_node_to_state[ssg.in_adj_list[n][i]] < si){
//					edges[si][e_count].target = map_node_to_state[n];
//					edges[si][e_count].source = map_node_to_state[ssg.in_adj_list[n][i]];
//					e_count++;
//				}
//			}
			for(int j=0; j<si; j++){
				int sn = map_state_to_node[j];
				for(i=0; i<ssg.out_adj_sizes[sn]; i++){
					if(ssg.out_adj_list[sn][i] == n){
						edges[si][e_count].source = j;
						edges[si][e_count].target = si;
						edges[si][e_count].attr = ssg.out_adj_attrs[sn][i];
						e_count++;
					}
				}
			}
		}

		delete[] node_flags;
		for(int i=0; i<nof_sn; i++)
			delete[] weights[i];
		delete[] weights;
		free(t_parent_node);
		delete[] t_parent_type;
	}





private:

	int wcompare(int i, int j, int** weights){
		for(int w=0; w<3; w++){
			if(weights[i][w] != weights[j][w]){
				return weights[j][w] - weights[i][w];
			}
		}
		return i-j;
	}

	void increase(int* ns, int* sis, int i, int** weights, int leftLimit){
		int temp;
		while(i>leftLimit &&   ( wcompare(ns[i], ns[i-1], weights) <0 ) ){
			temp = ns[i-1];
			ns[i-1] = ns[i];
			ns[i] = temp;

			temp = sis[ns[i-1]];
			sis[ns[i-1]] = sis[ns[i]];
			sis[ns[i]] = temp;

			i--;
		}
	}
};

}


#endif /* MAMACONSTRFIRST_H_ */
