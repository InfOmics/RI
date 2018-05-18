/*
 * Match.h
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

#ifndef MATCH_H_
#define MATCH_H_

#include "MatchListener.h"
#include "AttributeComparator.h"
#include "Solver.h"
#include "IsoGISolver.h"
#include "SubGISolver.h"
#include "InducedSubGISolver.h"

namespace rilib{

using namespace rilib;

enum MATCH_TYPE {MT_ISO, MT_INDSUB, MT_MONO};

void match(
		Graph&			reference,
		Graph& 			query,
		MatchingMachine&		matchingMachine,
		MatchListener& 			matchListener,
		MATCH_TYPE 				matchType,
		AttributeComparator& 	nodeComparator,
		AttributeComparator& 	edgeComparator,
		long* steps,
		long* triedcouples,
		long* matchedcouples){

	Solver* solver;
	switch(matchType){
	case MT_ISO:
		solver = new IsoGISolver(matchingMachine, reference, query, nodeComparator, edgeComparator, matchListener);
		break;
	case MT_INDSUB:
		solver = new InducedSubGISolver(matchingMachine, reference, query, nodeComparator, edgeComparator, matchListener);
		break;
	case MT_MONO:
		solver = new SubGISolver(matchingMachine, reference, query, nodeComparator, edgeComparator, matchListener);
		break;
	}

	solver->solve();

	*steps = solver->steps;
	*triedcouples = solver->triedcouples;
	*matchedcouples = solver->matchedcouples;

};

}




#endif /* MATCH_H_ */
