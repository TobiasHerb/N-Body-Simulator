/*
 * InputFileReader.h
 *
 *  Created on: May 29, 2012
 *      Author: Tobias Herb
 */

#ifndef INPUTFILEREADER_H_
#define INPUTFILEREADER_H_

// includes.
#include "../GlobalDefs.h"
#include "../Physics/Particle.h"
#include "../Math/Vector3D.h"
#include "NBodyApplication.h"
#include <list>
#include <fstream>

namespace NBodySimulation {

	class InputFileReader {
	public:
		InputFileReader( NBodyApplication::SimulationModel* simulationModel );

		virtual ~InputFileReader();

	private:
		NBodyApplication::SimulationModel* simulationModel;

	private:
		std::list<Physics::Particle<double,Math::Vector3D<double>>>* createParticlesFromInputFile( const char* filename );

		std::list<Physics::Particle<double,Math::Vector3D<double>>>* readModelFromFile( const char* filename );

	public:
		std::list<Physics::Particle<double,Math::Vector3D<double>>>* readFile( const char* filename );
	};
}

#endif /* INPUTFILEREADER_H_ */
