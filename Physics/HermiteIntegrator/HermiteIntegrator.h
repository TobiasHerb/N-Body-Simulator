/*
 * HermiteIntegrator.h
 *
 *  Created on: Jun 12, 2012
 *      Author: Tobias Herb
 */

#ifndef HERMITEINTEGRATOR_H_
#define HERMITEINTEGRATOR_H_

// includes.
#include "HMEquations.h"
#include "../Particle.h"
#include <list>
#include <limits>
#include <iostream>

namespace Physics {

	template<typename T,typename C> class HermiteIntegrator
		: public Physics::NumericIntegrator<T,C> {

	public:
		HermiteIntegrator( HMEquations<T,C>* equations ) {
			this->equations = equations;
			this->firstCall = true;
			this->ETA_S	= 0.01;
			this->ETA = 0.02;
			this->dt_min = pow( 2.0, -23.0 );
			this->dt_max = 0.125;
		}

		virtual ~HermiteIntegrator() {
			if( this->equations != 0L ) {
				delete equations;
				this->equations = 0L;
			}
		}

	private:
		HMEquations<T,C>* equations;

		bool 			  firstCall;

		double 	  ETA_S;

		double 	  ETA;

		double 	  dt_min;

		double 	  dt_max;

		bool	  allParticlesDone;

	private:
		double dmod( double x, double z ) {
			return ( ( x / z ) - ( (int)( x / z ) ) ) * z;
		}

	public:
		virtual EquationsBase<T,C>* getEquations() const {
			return this->equations;
		}

		virtual bool areAllParticlesDone() const {
			return this->allParticlesDone;
		}

		virtual void integrate( double& systemTime, std::list<Particle<T,C> >& particles, T timeDelta ) {

			if( this->firstCall ) {
				// calculate acceleration and jerk for all particles for the first time.
				double tmp = 0.0;
				for( Particle<T,C>& p : particles ) {

					// calculate acceleration and jerk.
					p.setAcceleration( Math::Vector3D<double>( 1.0, 1.0, 1.0 ) );
					p.setJerk( Math::Vector3D<double>( 10.0, 10.0, 10.0 ) );

					p.setPredictedVelocity( equations->updateVelocityPredictorStep( p.getVelocity(),
																					p.getAcceleration(),
																					p.getJerk(),
																					dt_min,
																					p.getParticleTime() ) );
					p.setPredictedPosition( equations->updatePositionPredictorStep( p.getPosition(),
																					p.getVelocity(),
																					p.getAcceleration(),
																					p.getJerk(),
																					dt_min,
																					p.getParticleTime() ) );

					p.setAcceleration( equations->updateAcceleration( p, particles ) );
					p.setJerk( equations->updateJerk( p, particles ) );

					if( p.getJerk().X() == 0.0 ||
						p.getJerk().Y() == 0.0 ||
						p.getJerk().Z() == 0.0 ) {

						if( p.getJerk().X() == 0.0 ) p.getJerk().set( pow( 1.0, -5.0 ), p.getJerk().Y(), p.getJerk().Z() );
						if( p.getJerk().Y() == 0.0 ) p.getJerk().set( p.getJerk().X(), pow( 1.0, -5.0 ), p.getJerk().Z() );
						if( p.getJerk().Z() == 0.0 ) p.getJerk().set( p.getJerk().X(), p.getJerk().Y(), pow( 1.0, -5.0 ) );

						p.setPredictedVelocity( equations->updateVelocityPredictorStep( p.getVelocity(),
																						p.getAcceleration(),
																						p.getJerk(),
																						dt_min,
																						p.getParticleTime() ) );
						p.setPredictedPosition( equations->updatePositionPredictorStep( p.getPosition(),
																						p.getVelocity(),
																						p.getAcceleration(),
																						p.getJerk(),
																						dt_min,
																						p.getParticleTime() ) );

						p.setAcceleration( equations->updateAcceleration( p, particles ) );
						p.setJerk( equations->updateJerk( p, particles ) );
					}

					tmp = ETA_S;
					double jerkLength = p.getJerk().length();
					if( jerkLength != 0.0 ) {
						tmp *= p.getAcceleration().length() / jerkLength;
					}
					double power = ( (int)( log( tmp ) / log( 2.0 ) ) ) - 1.0;
					tmp = pow( 2.0, power );
					if( tmp > dt_max )
						tmp = dt_max;
					if( tmp < dt_min )
						tmp = dt_min;

					p.setTimeStep( tmp );
				}

				firstCall = false;
			}

			// get minimum time step
			double minTime = std::numeric_limits<double>::max();
			double tmp = 0.0;
			for( Particle<T,C>& p : particles ) {
				tmp = p.getParticleTime() + p.getTimeStep();
				if( tmp < minTime ) {
					minTime = tmp;
				}
			}

			// get active particles
			std::list<Particle<T,C>*> activeParticles;
			for( Particle<T,C>& p : particles ) {
				if( p.getParticleTime() + p.getTimeStep() == minTime ) {
					activeParticles.push_back( &p );
				}
			}

			if( activeParticles.size() == particles.size() ) {
				this->allParticlesDone = true;
			} else {
				this->allParticlesDone = false;
			}

			// predictor step with ALL PARTICLES
			for( Particle<T,C>& p : particles ) {
				p.setPredictedPosition( equations->updatePositionPredictorStep(
															 p.getPosition(),
															 p.getVelocity(),
															 p.getAcceleration(),
															 p.getJerk(),
															 minTime,
															 p.getParticleTime() ) );

				p.setPredictedVelocity( equations->updateVelocityPredictorStep(
															 p.getVelocity(),
															 p.getAcceleration(),
															 p.getJerk(),
															 minTime,
															 p.getParticleTime() ) );
			}

			for( Particle<T,C>* p : activeParticles ) { // <- active particles.

				// calculate_acc_and_jerk()
				C acceleration_old = p->getAcceleration();

				p->setAcceleration( equations->updateAcceleration( (*p), particles ) );

				C jerk_old = p->getJerk();
				p->setJerk( equations->updateJerk( (*p), particles ) );

				C snap_old = equations->updateSnap( acceleration_old,
													p->getAcceleration(),
													jerk_old,
													p->getJerk(),
													p->getTimeStep() );

				C crackle_old = equations->updateCrackle( acceleration_old,
														  p->getAcceleration(),
														  jerk_old,
														  p->getJerk(),
														  p->getTimeStep() );

				// corrector_step()
				p->setVelocity( equations->updateVelocity( p->getPredictedVelocity(),
														   snap_old,
														   crackle_old,
														   p->getTimeStep() ) );

				p->setPosition( equations->updatePosition( p->getPredictedPosition(),
														   snap_old,
														   crackle_old,
														   p->getTimeStep() ) );

				C snap_new = snap_old + crackle_old * p->getTimeStep();
				C crackle_new = crackle_old;

				double newTimeStep = equations->updateTimeStep( p->getAcceleration(),
														  p->getJerk(),
														  snap_new,
														  crackle_new,
														  ETA );

				double dt_tmp = p->getTimeStep();
				if( newTimeStep < dt_min )
					newTimeStep = dt_min;
				if( newTimeStep < dt_tmp && newTimeStep > dt_min ) {
					double power = ( (int)( log( newTimeStep ) / log( 2.0 ) ) ) - 1.0;
					dt_tmp = pow( 2.0, power );
				}
				if( ( newTimeStep > 2.0 * dt_tmp ) &&
					( dmod( minTime, 2.0 * dt_tmp ) == 0.0 ) &&
					( 2.0 * dt_tmp < dt_max ) )
					dt_tmp = 2.0 * dt_tmp;

				p->setTimeStep( dt_tmp );
				p->setParticleTime( minTime );
			}

			systemTime = minTime;
		}
	};
}

#endif /* HERMITEINTEGRATOR_H_ */
