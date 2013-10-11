/*
 * LeapfrogIntegrator.h
 *
 *  Created on: May 17, 2012
 *      Author: Tobias Herb
 */

#ifndef LEAPFROGINTEGRATOR_H_
#define LEAPFROGINTEGRATOR_H_

// includes.
#include "../Particle.h"
#include "LFEquations.h"
#include <list>

namespace Physics {

	template<typename T,typename C> class LeapfrogIntegrator
		: public Physics::NumericIntegrator<T,C> {

	public:
		LeapfrogIntegrator( LFEquations<T,C>* equations ) {
			this->equations = equations;
		}

		virtual ~LeapfrogIntegrator() {
			if( this->equations != 0L ) {
				delete equations;
				this->equations = 0L;
			}
		}
	private:
		LFEquations<T,C>* equations;

	public:
		EquationsBase<T,C>* getEquations() const {
			return this->equations;
		}

		virtual void integrate( double& systemTime, std::list<Particle<T,C> >& particles, T timeDelta ) {
			for( Particle<T,C>& p : particles ) {
				p.setPosition( equations->updatePosition( p.getPosition(),
															   p.getVelocity(),
															   p.getAcceleration(),
															   timeDelta ) );
			}
			std::list<C> oldAccelerations;
			for( Particle<T,C>& p : particles ) {
				oldAccelerations.push_back( p.getAcceleration() );
				p.setAcceleration( equations->updateAcceleration( p, particles ) );
			}
			auto iter = oldAccelerations.begin();
			for( Particle<T,C>& p : particles ) {
				p.setVelocity( equations->updateVelocity( p.getVelocity(),
															   (*iter),
															   p.getAcceleration(),
															   timeDelta ) );
				iter++;
				p.setParticleTime( p.getParticleTime() + timeDelta );
			}

			systemTime += timeDelta;
		}
	};
}

#endif /* LEAPFROGINTEGRATOR_H_ */
