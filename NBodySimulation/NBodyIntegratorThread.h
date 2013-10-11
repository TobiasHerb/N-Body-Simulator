/*
 * NBodyIntegratorThread.h
 *
 *  Created on: Jun 1, 2012
 *      Author:
 */

#ifndef NBODYINTEGRATORTHREAD_H_
#define NBODYINTEGRATORTHREAD_H_

// includes.
#include "../Application/Thread.h"
#include "NBodyApplication.h"
#include "../Physics/NumericIntegrator.h"
#include "../Math/Vector3D.h"

namespace NBodySimulation {

	// forward declaration.
	//class NBodyApplication::SimulationModel; // pfui, not possible in C++...

	class NBodyIntegratorThread : public Application::Thread<NBodyIntegratorThread> {
	public:
		NBodyIntegratorThread();

		virtual ~NBodyIntegratorThread();

	private:
		NBodyApplication::SimulationModel*	simulationModel;

		Physics::NumericIntegrator<double,Math::Vector3D<double>>*	integrator;

		bool	firstCall;

		bool 	isWritten;

	public:
		inline void setSimulationModel( NBodyApplication::SimulationModel*	simulationModel ) {
			this->simulationModel = simulationModel;
		}

		void* runThread( void* args );
	};
}

#endif /* NBODYINTEGRATORTHREAD_H_ */
