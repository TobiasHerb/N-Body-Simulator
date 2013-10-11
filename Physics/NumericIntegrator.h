/*
 * NumericIntegrator.h
 *
 *  Created on: Jun 14, 2012
 *      Author: Tobias Herb
 */

#ifndef NUMERICINTEGRATOR_H_
#define NUMERICINTEGRATOR_H_

// includes.
#include <list>
#include "Particle.h"
#include "EquationsBase.h"

namespace Physics {

	template<typename T,typename C> class NumericIntegrator {
	public:

		virtual void integrate( double& systemTime, std::list<Particle<T,C>>& particles, T timeDelta ) = 0;

		virtual EquationsBase<T,C>* getEquations() const = 0;

		virtual bool areAllParticlesDone() const {
			return true;
		}
	};
}

#endif /* NUMERICINTEGRATOR_H_ */
