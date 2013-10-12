/*
 * PlummerModelGenerator.h
 *
 *  Created on: Jun 13, 2012
 *      Author: Tobias Herb
 */

#ifndef PLUMMERMODELGENERATOR_H_
#define PLUMMERMODELGENERATOR_H_

// includes.
#include "../../GlobalDefs.h"
#ifdef _USE_HERMITE_INTEGRATOR_
	#include "../Particle.h"
#else
	#include "../Particle.h"
#endif
#include "../../Math/Vector3D.h"
#include <list>

namespace Physics {

	class PlummerModelGenerator {
	public:
		PlummerModelGenerator();

		virtual ~PlummerModelGenerator();

	public:
		std::list<Particle<double,Math::Vector3D<double>>>* generateModel( int particleCount );

		void generateModelAndWriteToFile( const char* filename, int particleCount );
	};
}

#endif /* PLUMMERMODELGENERATOR_H_ */
