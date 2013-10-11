/*
 * IntegratorFactory.h
 *
 *  Created on: Jun 19, 2012
 *      Author: Tobias Herb
 */

#ifndef INTEGRATORFACTORY_H_
#define INTEGRATORFACTORY_H_

// includes.
#include "NumericIntegrator.h"
#include "HermiteIntegrator/HermiteIntegrator.h"
#include "LeapfrogIntegrator/LeapfrogIntegrator.h"
#include <iostream>

namespace Physics {

	enum IntegratorType {

		INTEGRATOR_LEAPFROG = 0,

		INTEGRATOR_HERMITE	= 1
	};

	template<typename T, typename C> class IntegratorFactory {
	public:
		static NumericIntegrator<T,C>* createIntegrator( IntegratorType type ) {
			switch( type ) {
				case INTEGRATOR_LEAPFROG: {
					EquationsBase<T,C>* eqBase = new LFEquations<T,C>();
					NumericIntegrator<T,C>* integrator =
							new LeapfrogIntegrator<T,C>(
									static_cast<LFEquations<T,C>*>( eqBase ) );
					return integrator;
				};
				case INTEGRATOR_HERMITE: {
					EquationsBase<T,C>* eqBase =
							new HMEquations<T,C>();
					NumericIntegrator<T,C>* integrator =
							new HermiteIntegrator<T,C>(
									static_cast<HMEquations<T,C>*>( eqBase ) );
					return integrator;
				};
				default: {
					std::cerr << "Integrator type not supported." << std::endl;
					return 0L;
				}
			}
		}
	};
}

#endif /* INTEGRATORFACTORY_H_ */
