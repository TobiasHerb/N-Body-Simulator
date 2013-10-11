/*
 * HMEquations.h
 *
 *  Created on: Jun 18, 2012
 *      Author: Tobias Herb
 */

#ifndef HMEQUATIONS_H_
#define HMEQUATIONS_H_

// includes.
#include "../EquationsBase.h"
#include <list>
#include <iostream>

namespace Physics {

	template<typename T,typename C> class HMEquations : public EquationsBase<T,C> {
	public:
		HMEquations() {
			epsilon = 0; //pow( 10.0, -12.0 );
		}
		virtual ~HMEquations() {
		}
	private:
		T epsilon;

	public:
		virtual C updatePosition( C pred_position,
								 C snap,
								 C crackle,
								 T timeDelta ) {
			return pred_position + ( snap * ( pow( timeDelta, 4.0 ) / 24.0 ) ) + ( crackle * ( pow( timeDelta, 5.0 ) / 120.0 ) );
		}

		virtual C updateVelocity( C pred_velocity,
								  C snap,
								  C crackle,
								  T timeDelta ) {
			return pred_velocity + ( snap * ( pow( timeDelta, 3.0 ) / 6.0 ) ) + ( crackle * ( pow( timeDelta, 4.0 ) / 24.0 ) );
		}

		virtual C updatePositionPredictorStep( C position,
											  C velocity,
											  C acceleration,
											  C jerk,
											  T systemTime,
											  T particleTime ) {

			T timeDiff = systemTime - particleTime;
			return position + ( velocity * timeDiff ) + acceleration * ( ( timeDiff * timeDiff ) / 2.0 ) + ( ( jerk * ( pow( timeDiff, 3.0 ) ) / 6.0 ) );
		}

		virtual C updateVelocityPredictorStep( C velocity,
											   C acceleration,
											   C jerk,
											   T systemTime,
											   T particleTime ) {
			T timeDiff = systemTime - particleTime;
			return velocity + ( acceleration * timeDiff ) + ( jerk * ( pow( timeDiff, 2.0 ) / 2.0 ) );
		}

		virtual C updateAcceleration( Particle<T,C>& px, std::list<Particle<T,C>>& particles ) {
			C a;
			for( Particle<T,C>& pi : particles ) {
				if( !(px == pi) ) {
					C tmp;
					C r_ij = pi.getPredictedPosition() - px.getPredictedPosition();
					double divisor = pow( ( r_ij.length() * r_ij.length() ) + ( epsilon * epsilon ), ( 3.0 / 2.0 ) );
					if( divisor == 0.0 ) {
						std::cout << "updateAcceleration: DIVISION BY ZERO" << std::endl;
					}
					tmp = ( ( r_ij ) / divisor );
					tmp *= CommonPhysics::G * pi.getMass();
					a += tmp;
				}
			}
			return a;
		}

		virtual C updateJerk( Particle<T,C>& px, std::list<Particle<T,C>>& particles ) {
			C j;
			for( Particle<T,C>& pi : particles ) {
				if( !(px == pi) ) {
					C tmp;
					C r_ij = pi.getPredictedPosition() - px.getPredictedPosition();
					C v_ij = pi.getPredictedVelocity() - px.getPredictedVelocity();
					double divisor = pow( r_ij.length() * r_ij.length() + epsilon * epsilon, ( 3.0 / 2.0 ) );
					if( divisor == 0.0 ) {
						std::cout << "updateJerk (1): DIVISION BY ZERO" << std::endl;
					}
					tmp = v_ij / divisor;
					divisor = pow( ( r_ij.length() * r_ij.length() + epsilon * epsilon ), ( 5.0 / 2.0 ) );
					if( divisor == 0.0 ) {
						std::cout << "updateJerk (2): DIVISION BY ZERO" << std::endl;
					}
					tmp += ( ( r_ij * ( v_ij * r_ij ) ) * 3.0 ) / divisor;
					tmp *= CommonPhysics::G * pi.getMass();
					j += tmp;
				}
			}
			return j;
		}

		virtual C updateSnap( C acceleration_old,
							  C acceleration_new,
							  C jerk_old,
							  C jerk_new,
							  T timeDelta ) {
			return ( ( ( acceleration_old - acceleration_new ) * (-6.0) ) - ( ( jerk_old * 4.0 + jerk_new * 2.0 ) * timeDelta ) )  / ( timeDelta * timeDelta );
		}

		virtual C updateCrackle( C acceleration_old,
							  C acceleration_new,
							  C jerk_old,
							  C jerk_new,
							  T timeDelta ) {
			return ( ( ( acceleration_old - acceleration_new ) * (12.0) ) + ( ( jerk_old + jerk_new ) * ( timeDelta * 6.0 ) ) ) / ( pow( timeDelta, 3.0 ) );
		}

		virtual T updateTimeStep( C acceleration_new,
								  C jerk_new,
								  C snap_new,
								  C crackle_new,
								  T eta ) {

			return sqrt( eta * ( ( acceleration_new.length() * snap_new.length() + ( jerk_new.length() * jerk_new.length() ) ) /
					( jerk_new.length() * crackle_new.length() + ( snap_new.length() * snap_new.length() ) ) ) );
		}
	};
}

#endif /* HMEQUATIONS_H_ */
