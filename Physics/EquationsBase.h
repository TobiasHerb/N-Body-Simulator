/*
 * EquationsBase.h
 *
 *  Created on: Jun 18, 2012
 *      Author: Tobias Herb
 */

#ifndef EQUATIONSBASE_H_
#define EQUATIONSBASE_H_

// includes.
#include "CommonPhysics.h"
#include "Particle.h"
#include <iostream>

namespace Physics {

	template<typename T, typename C> class EquationsBase {
	public:
		virtual ~EquationsBase() {
		}
	public:
		virtual T updateKineticEnergy( std::list<Particle<T, C>>& particles ) {
			T k = T();
			for( Particle<T, C>& p : particles ) {
				k += 0.5 * ( p.getVelocity().length() * p.getVelocity().length() ) * p.getMass();
			}
			return k;
		}

		virtual T updatePotentialEnergy( std::list<Particle<T,C>>& particles ) {
			T u = T();
			for( Particle<T, C>& i : particles ) {
				T u_i = T();
				for( Particle<T, C>& j : particles ) {
					if( !(i == j) ) {
						C r_ij = i.getPosition() - j.getPosition();
						if( r_ij.length() != 0 ) { // TODO: richtig???
							u_i += ( i.getMass() * j.getMass() ) / r_ij.length();
						}
					}
				}
				u_i *= -CommonPhysics::G;
				u += u_i;
			}
			u *= 0.5;
			return u;
		}

		virtual C updateCenterOfMassPosition( std::list<Particle<T, C>>& particles ) {
			C r = C();
			for( Particle<T, C>& i : particles ) {
				r += ( i.getPosition() * i.getMass() );
			}
			r /= particles.size();
			return r;
		}

		virtual C updateCenterOfMassVelocity( std::list<Particle<T, C>>& particles ) {
			C r = C();
			for( Particle<T, C>& i : particles ) {
				r += ( i.getVelocity() * i.getMass() );
			}
			r /= particles.size();
			return r;
		}
	};
}

#endif /* EQUATIONSBASE_H_ */
