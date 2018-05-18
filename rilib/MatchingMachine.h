/*
 * MatchingMachine.h
 *
 *  Created on: Aug 3, 2012
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

#ifndef MATCHINGMACHINE_H_
#define MATCHINGMACHINE_H_

#include "Graph.h"

namespace rilib{


class MaMaEdge{
public:
	int source;
	int target;
	void* attr;

	MaMaEdge(int _source, int _target, void* _attr){
		source = _source;
		target = _target;
		attr = _attr;
	}

	MaMaEdge(){
		source = -1;
		target = -1;
		attr = NULL;
	}
};

enum MAMA_PARENTTYPE {PARENTTYPE_IN, PARENTTYPE_OUT, PARENTTYPE_NULL};

class MatchingMachine{
public:

	int nof_sn;

	void** nodes_attrs;				//indexed by state_id
	int* edges_sizes;				//indexed by state_id
	int* o_edges_sizes;				//indexed by state_id
	int* i_edges_sizes;				//indexed by state_id
	MaMaEdge** edges;				//indexed by state_id, map on states  (0,1) = (state0, state1)

	int* map_node_to_state;			//indexed by node_id
	int* map_state_to_node;			//indexed by state_id

	int* parent_state;				//indexed by state_id
	MAMA_PARENTTYPE* parent_type;	//indexed by state id


	MatchingMachine(Graph& query){

		nof_sn = query.nof_nodes;
		nodes_attrs = new void*[nof_sn];
		edges_sizes = (int*) calloc(nof_sn, sizeof(int));
		o_edges_sizes = (int*) calloc(nof_sn, sizeof(int));
		i_edges_sizes = (int*) calloc(nof_sn, sizeof(int));
		edges = new MaMaEdge*[nof_sn];

		map_node_to_state = (int*) calloc(nof_sn, sizeof(int));
		map_state_to_node = (int*) calloc(nof_sn, sizeof(int));
		parent_state = (int*) calloc(nof_sn, sizeof(int));
		parent_type = new MAMA_PARENTTYPE[nof_sn];

		//build(query);
	}

	virtual ~MatchingMachine(){
		delete[] nodes_attrs;
		for(int i=0; i<nof_sn; i++){
			delete[] edges[i];
		}
		delete[] edges;
		free(edges_sizes);
		free(o_edges_sizes);
		free(i_edges_sizes);
		free(map_node_to_state);
		free(map_state_to_node);
		free(parent_state);
		delete[] parent_type;
	}


	void print(){
		std::cout<<"| MatchingMachine:  nof sates "<<nof_sn<<"\n";
		std::cout<<"| \tmap state_to_node(";
		for(int i=0; i< nof_sn; i++){
			std::cout<<"["<<i<<":"<<map_state_to_node[i]<<"]";
		}
		std::cout<<")\n";
		std::cout<<"| \tmap node_to_state(";
		for(int i=0; i< nof_sn; i++){
			std::cout<<"["<<i<<":"<<map_node_to_state[i]<<"]";
		}
		std::cout<<")\n";
		std::cout<<"| \tstates (node)(parent state, parent type)\n";
		for(int i=0; i<nof_sn; i++){
			std::cout<<"| \t\t["<<i<<"] ("<<map_state_to_node[i]<<") ("<<parent_state[i]<<", ";
			switch(parent_type[i]){
			case PARENTTYPE_IN:
				std::cout<<"IN";
				break;
			case PARENTTYPE_OUT:
				std::cout<<"OUT";
				break;
			case PARENTTYPE_NULL:
				std::cout<<"NULL";
				break;
			}
			std::cout<<")\n";
			std::cout<<"| \t\t\tchecking["<<edges_sizes[i]<<"] ";
			for(int j=0; j<edges_sizes[i]; j++){
				std::cout<<"{s("<<edges[i][j].source<<","<<edges[i][j].target<<"):";
				std::cout<<"n("<<map_state_to_node[edges[i][j].source]<<","<<map_state_to_node[edges[i][j].target]<<")}";
			}
			std::cout<<"\n";
		}
	}




public:

	virtual void build(Graph& ssg)=0;
};

}


#endif /* MATCHINGMACHINE_H_ */
