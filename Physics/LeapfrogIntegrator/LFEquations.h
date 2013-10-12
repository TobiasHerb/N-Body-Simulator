/*
 * LFEquations.h
 *
 *  Created on: Jun 18, 2012
 *      Author: Tobias Herb
 */

#ifndef LFEQUATIONS_H_
#define LFEQUATIONS_H_

// includes.
#include "../EquationsBase.h"
#include <list>

namespace Physics {

	template<typename T,typename C> class LFEquations : public EquationsBase<T,C> {
	public:
		virtual ~LFEquations() {
		}

	public:
		virtual C updatePosition( C position,
					  C velocity,
					  C acceleration,
					  T timeDelta ) {

			return position + ( velocity * timeDelta ) + ( ( acceleration * ( timeDelta * timeDelta ) ) / 2 );
		}


		virtual C updateVelocity( C velocity,
					  C accCurrent,
					  C accNext,
					  T timeDelta ) {

			return velocity + ( ( ( accCurrent + accNext ) * timeDelta ) / 2 );
		}

		virtual C updateAcceleration( Particle<T,C>& px, std::list<Particle<T,C>>& particles ) {
			C a;
			for( Particle<T,C>& pi : particles ) {
				if( (&px) != (&pi) ) {
					C r_ij = px.getPosition() - pi.getPosition();
					a += ( ( r_ij * pi.getMass() ) / ( pow( r_ij.length(), 3.0 ) ) );
				}
			}
			a = a * -CommonPhysics::G;
			return a;
		}
	};
}

#endif /* LFEQUATIONS_H_ */
