/*
 * NBodyIntegratorThread.cpp
 *
 *  Created on: Jun 1, 2012
 *      Author: Tobias Herb
 */

// includes.
#include "../GlobalDefs.h"
#include "NBodyIntegratorThread.h"
#include "../Math/Vector3D.h"
#include "../Math/CommonMath.h"
#include "../Physics/IntegratorFactory.h"
#include <list>
#include <iostream>
#include <time.h>
#include <fstream>
#include <cmath>

namespace NBodySimulation {

	NBodyIntegratorThread::NBodyIntegratorThread() {
		this->firstCall = true;
		this->isWritten = false;
	}

	NBodyIntegratorThread::~NBodyIntegratorThread() {
		if( this->integrator != 0L ) {
			delete this->integrator;
			this->integrator = 0L;
		}
	}

	void* NBodyIntegratorThread::runThread( void* args ) {

		// Just Sleep a bit.
		time_t start_time, cur_time;
		time( &start_time );
		do{ time( &cur_time ); } while( ( cur_time - start_time ) < 2 );

		this->integrator = Physics::IntegratorFactory<double,Math::Vector3D<double>>::
				createIntegrator( this->simulationModel->integratorType );

		std::ofstream file( "plummer1.dat" );

		while( !this->simulationModel->isSimulationFinished ) {

			if( this->simulationModel->isSimulationRunning ) {
				// ensure atomic behavior
				this->lock();

				if( this->firstCall ) {
					this->simulationModel->kineticEnergy   = this->integrator->getEquations()->updateKineticEnergy( (*this->simulationModel->particles) );
					this->simulationModel->potentialEnergy = this->integrator->getEquations()->updatePotentialEnergy( (*this->simulationModel->particles) );
					this->simulationModel->totalEnergyStartup = this->simulationModel->kineticEnergy + this->simulationModel->potentialEnergy;
					this->simulationModel->totalEnergy = this->simulationModel->totalEnergyStartup;
					file << 0.0 << "   " << this->simulationModel->totalEnergy << std::endl;
					this->firstCall = false;
				}

				this->integrator->integrate( this->simulationModel->systemTime,
											 (*this->simulationModel->particles),
											 this->simulationModel->integrationStepWidth );

				this->simulationModel->centerOfMassPosition = this->integrator->getEquations()->
						updateCenterOfMassPosition( (*this->simulationModel->particles) );

				//if( this->integrator->areAllParticlesDone() ) {
					this->simulationModel->kineticEnergy   = this->integrator->getEquations()->updateKineticEnergy( (*this->simulationModel->particles) );
					this->simulationModel->potentialEnergy = this->integrator->getEquations()->updatePotentialEnergy( (*this->simulationModel->particles) );
					this->simulationModel->totalEnergy = this->simulationModel->kineticEnergy + this->simulationModel->potentialEnergy;

					if( this->simulationModel->elapsedTime % 10 == 0 && isWritten == false ) {
						file << this->simulationModel->systemTime << "   " << this->simulationModel->totalEnergy << std::endl;
						isWritten = true;
					} else {
						if( this->simulationModel->elapsedTime % 10 != 0 ) {
							isWritten = false;
						}
					}
				//}

				this->unlock();
			}

			//if( this->simulationModel->totalEnergyStartup == -1.0 ) {
			//	this->simulationModel->totalEnergyStartup = this->simulationModel->totalEnergy;
			//}

			if( this->simulationModel->isSimulationRunning ) {
				time_t currentTime;
				time( &currentTime );
				this->simulationModel->elapsedTime = ( currentTime - this->simulationModel->startTime );
			} else {
			}

			if( this->simulationModel->simulationRuntime > 0 &&
				this->simulationModel->simulationRuntime <= this->simulationModel->systemTime ) {
				this->simulationModel->isSimulationRunning = false;
				this->simulationModel->isSimulationFinished = true;
			}
		}

		std::cout << (*(*this->simulationModel->particles).begin()).getParticleTime() << std::endl;
		return 0L;
	}
}
