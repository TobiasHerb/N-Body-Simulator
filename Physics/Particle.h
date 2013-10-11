/*
 * Particle.h
 *
 *  Created on: May 15, 2012
 *      Author: Tobias Herb
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

// includes.
#include <string>
#include <sstream>
#include <list>

namespace Physics {

	template<typename T, typename C> class Particle {
	public:
		Particle() {
			this->mass = 0;

			this->time			= 0;
			this->timeStep		= 0.00000000000001;
		}

		Particle( T mass, C jerk, C acceleration, C velocity, C position ) {
			this->mass = mass;
			this->jerk = jerk;
			this->acceleration = acceleration;
			this->velocity = velocity;
			this->position = position;

			this->time			= 0;
			this->timeStep		= 0.0000001;
		}

		Particle( const Particle<T,C>& p ) {
			this->mass 			= p.mass;
			this->jerk			= p.jerk;
			this->acceleration 	= p.acceleration;
			this->velocity 		= p.velocity;
			this->position 		= p.position;
			//
			this->predicted_position = p.predicted_position;
			this->predicted_velocity = p.predicted_velocity;
			//
			this->time			= p.time;
			this->timeStep		= p.timeStep;
			//
		}

	private:
		T 	mass;
		C 	acceleration;
		C	velocity;
		C 	position;
		C	jerk;

		//
		C	predicted_position;
		C	predicted_velocity;
		//

		//
		std::list<C>	particleTrace;
		//

		//
		T	time;
		T	timeStep;
		//

	public:
		Particle<T,C>& operator=( const Particle<T,C>& p ) {
			this->mass 			= p.mass;
			this->jerk			= p.jerk;
			this->acceleration 	= p.acceleration;
			this->velocity 		= p.velocity;
			this->position 		= p.position;
			//
			this->predicted_position = p.predicted_position;
			this->predicted_velocity = p.predicted_velocity;
			//
			this->time			= p.time;
			this->timeStep		= p.timeStep;
			//
			return (*this);
		}

		T getMass() const {
			return this->mass;
		}

		void setMass( const T mass ) {
			this->mass = mass;
		}

		C getJerk() const {
			return this->jerk;
		}

		void setJerk( const C& jerk ) {
			this->jerk = jerk;
		}

		C getAcceleration() const {
			return this->acceleration;
		}

		void setAcceleration( const C& acceleration ) {
			this->acceleration = acceleration;
		}

		C getVelocity() const {
			return this->velocity;
		}

		void setVelocity( const C& velocity ) {
			this->velocity = velocity;
		}

		C getPosition() const {
			return position;
		}

		void setPosition( const C& position ) {
			this->position = position;
		}

		// ----
		void setPredictedPosition( const C& predicted_position ) {
			this->predicted_position = predicted_position;
		}

		C getPredictedPosition() const {
			return this->predicted_position;
		}

		void setPredictedVelocity( const C& predicted_velocity ) {
			this->predicted_velocity = predicted_velocity;
		}

		C getPredictedVelocity() const {
			return this->predicted_velocity;
		}
		// ----

		void setParticleTime( const T& time ) {
			this->time = time;
		}

		T getParticleTime() const {
			return this->time;
		}

		void setTimeStep( const T& timeStep ) {
			this->timeStep = timeStep;
		}

		T getTimeStep() const {
			return this->timeStep;
		}

		void set( T mass, C jerk, C acceleration, C velocity, C position ) {
			this->mass = mass;
			this->jerk = jerk;
			this->acceleration = acceleration;
			this->velocity = velocity;
			this->position = position;
		}

		//
		void set( T mass, C jerk, C acceleration, C velocity, C position,
				  C predicted_position, C predicted_velocity /*, C predicted_acceleration, C predicted_jerk*/ ) {
			this->mass = mass;
			this->jerk = jerk;
			this->acceleration = acceleration;
			this->velocity = velocity;
			this->position = position;
			this->predicted_position = predicted_position;
			this->predicted_velocity = predicted_velocity;
		}
		//

		std::string toString() const {
			std::stringstream ss;
			ss << "[ mass: " << this->mass << "," << std::endl
			   << "  jerk: " << this->jerk.toString() << std::endl
			   << "  acc: " << this->acceleration.toString() << std::endl
			   << "  vel: " << this->velocity.toString() << std::endl
			   << "  pos: " << this->position.toString() << "]";
			return ss.str();
		}

		//
		void addTraceElement( const C& v ) {
			this->particleTrace.push_back( v );
		}

		std::list<C> getParticleTrace() const {
			return this->particleTrace;
		}
		//

		bool operator==( const Particle<T,C>& p ) const {
			if( this == &p )
				return true;
			if( this->mass == p.mass &&
				this->acceleration == p.acceleration &&
				this->velocity == p.velocity &&
				this->position == p.position )
				return true;
			// TODO: fulfills not exact equals contract...
			return false;
		}
	};
}

#endif /* PARTICLE_H_ */
