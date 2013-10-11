/*
 * NBodyApplication.h
 *
 *  Created on: May 16, 2012
 *      Author: Tobias Herb
 */

#ifndef NBODYAPPLICATION_H_
#define NBODYAPPLICATION_H_

// inlcudes.
#include "../GlobalDefs.h"
#include "../Application/OpenGLApplication.h"
#include "../Math/Vector3D.h"
#include "../Physics/Particle.h"
#include "../Physics/IntegratorFactory.h"
#include <list>
#include <ctime>

namespace NBodySimulation {

	// forward declaration.
	class NBodyIntegratorThread;
	class InputFileReader;

	class NBodyApplication : public Application::OpenGLApplication {
	public:

		typedef struct _SimulationModel {

			_SimulationModel() {
				this->simulationRuntime		= 5;
				this->integrationStepWidth	= 0.000001;
				this->isSimulationRunning 	= true;
				this->areVectorsShown 		= false;
				this->isCenterOfMassShown	= false;
				this->startTime 			= 0;
				this->elapsedTime 			= 0;
				this->kineticEnergy 		= 0;
				this->potentialEnergy 		= 0;
				this->totalEnergy 			= 0;
				this->totalEnergyStartup	= -1.0;
				this->particles 			= 0L;
				this->initialParticles 		= 0L;
				this->isSimulationFinished	= false;
				this->isTraceModeEnabled	= false;
				this->integratorType		= Physics::IntegratorType::INTEGRATOR_LEAPFROG;
				this->systemTime			= 0.0;
			}

			~_SimulationModel() {
				if( this->particles != 0L ) {
					delete this->particles;
				}
				if( this->initialParticles != 0L ) {
					delete this->initialParticles;
				}
			}

			bool 				isSimulationRunning;

			bool 				isSimulationFinished;

			bool				areVectorsShown;

			bool				isCenterOfMassShown;

			bool				isTraceModeEnabled;

			time_t 				startTime;

			time_t 				elapsedTime;

			time_t 				simulationRuntime;

			double				integrationStepWidth;

			double 				kineticEnergy;

			double 				potentialEnergy;

			double 				totalEnergy;

			double 				totalEnergyStartup;

			double 				systemTime;

			Math::Vector3D<double>	centerOfMassPosition;

			std::list<Physics::Particle<double,Math::Vector3D<double>>>* particles;

			std::list<Physics::Particle<double,Math::Vector3D<double>>>* initialParticles;

			Physics::IntegratorType integratorType;

		} SimulationModel;

	public:
		NBodyApplication( std::string name,
				 	 	  Math::Vector2D<int> position,
				 	 	  Math::Dimension2D<int> size );

		virtual ~NBodyApplication();

	private:
		NBodySimulation::InputFileReader*			fileReader;

		SimulationModel*							simulationModel;

		NBodyIntegratorThread*						integratorThread;

	public:
		void initialize( int argc, char **argv );

		void shutdown();

		inline SimulationModel* getSimulationModel() const {
			return simulationModel;
		}

		inline NBodyIntegratorThread* getIntegratorThread() const {
			return integratorThread;
		}

	protected:
		void processNormalKey( unsigned char key, int x, int y );

	private:
		void menuHandler( int value );

		static void static_menuHandler( int value );
	};
}

#endif /* NBODYAPPLICATION_H_ */
