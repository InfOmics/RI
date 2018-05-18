/*
 * IsoSolver.h
 *
 *  Created on: Aug 4, 2012
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

#ifndef ISOSOLVER_H_
#define ISOSOLVER_H_


#include "Solver.h"

namespace rilib{


class IsoGISolver : public Solver{
public:

	IsoGISolver(
				MatchingMachine& _mama,
				Graph& _rgraph,
				Graph& _qgraph,
				AttributeComparator& _nodeComparator,
				AttributeComparator& _edgeComparator,
				MatchListener& _matchListener
				) : Solver(_mama, _rgraph, _qgraph, _nodeComparator, _edgeComparator, _matchListener){

	}


	virtual bool nodeCheck(int si, int ci, int* map_state_to_node){
		if(			rgraph.out_adj_sizes[ci] == qgraph.out_adj_sizes[map_state_to_node[si]]
		   		    && rgraph.in_adj_sizes[ci] == qgraph.in_adj_sizes[map_state_to_node[si]]){
			return nodeComparator.compare(rgraph.nodes_attrs[ci], qgraph.nodes_attrs[map_state_to_node[si]]);
		}
		return false;
	}

	virtual bool edgesCheck(int si, int ci, int* solution, bool* matched){
		int source, target;
		int ii;
		for(int me=0; me<mama.edges_sizes[si]; me++){
			source = solution[ mama.edges[si][me].source ];
			target = solution[ mama.edges[si][me].target ];

			for(ii=0; ii<rgraph.out_adj_sizes[source]; ii++){
				if(rgraph.out_adj_list[source][ii] == target){
//					if(! edgeComparator.compare(rgraph.out_adj_attrs[source][ii],  mama.edges[si][me].attr)){
//						return false;
//					}
//					else{
//						break;
//					}
					if(edgeComparator.compare(rgraph.out_adj_attrs[source][ii],  mama.edges[si][me].attr)){
						break;
					}
				}
			}
			if(ii >= rgraph.out_adj_sizes[source]){
				return false;
			}
		}
		return true;
	}
};

}


#endif /* ISOSOLVER_H_ */
