/*
 * MTHMEquations.h
 *
 *  Created on: Jul 3, 2012
 *      Author: Tobias Herb
 */

#ifndef MTHMEQUATIONS_H_
#define MTHMEQUATIONS_H_

// includes.
#include "../EquationsBase.h"
#include <list>
#include <iostream>

namespace Physics {

	template<typename T,typename C> class MTHMEquations : public EquationsBase<T,C> {
	public:
		MTHMEquations() {
		}

		virtual ~MTHMEquations() {
		}

	public:
		/*
		virtual C updatePositionPredictorStep( C position,
											   C velocity,
											   C acceleration,
											   C jerk,
											   T timeDelta ) {
			return position +
				   ( velocity * timeDelta ) +
				   ( acceleration * ( 1.0 / 2.0 ) * pow( timeDelta, 2.0 ) ) +
				   ( jerk * ( 1.0 / 6.0 ) * pow( timeDelta, 3.0 ) );
		}

		virtual C updateVelocityPredictorStep( C velocity,
											   C acceleration,
											   C jerk,
											   T timeDelta ) {
			return velocity +
				   ( acceleration * timeDiff ) +
				   ( jerk * ( 1.0 / 2.0 ) * pow( timeDelta, 2.0 ) ) );
		}
		*/
	};
}

#endif /* MTHMEQUATIONS_H_ */
