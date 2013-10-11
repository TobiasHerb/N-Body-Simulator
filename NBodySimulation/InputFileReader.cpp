/*
 * InputFileReader.cpp
 *
 *  Created on: May 29, 2012
 *      Author: Tobias Herb
 */

// includes.
#include "InputFileReader.h"
#include <iostream>

namespace NBodySimulation {

	InputFileReader::InputFileReader( NBodyApplication::SimulationModel* simulationModel ) {
		this->simulationModel = simulationModel;
	}

	InputFileReader::~InputFileReader() {
	}

	std::list<Physics::Particle<double,Math::Vector3D<double>>>* InputFileReader::createParticlesFromInputFile( const char* filename ) {

		std::ifstream file( filename );
	    if ( !file.is_open() ) {
	    	std::cerr << "could not open file" << std::endl;
	    	return 0L;
	    } else {
	    	auto particles = new std::list<Physics::Particle<double,Math::Vector3D<double>>>();
	    	int c = 0;
	    	file >> c;
	    	file >> this->simulationModel->integrationStepWidth;
	    	file >> this->simulationModel->simulationRuntime;

	    	for( int i = 0; i < c; ++i ) {

	    		double mass = 0.0;
				double posx = 0.0, posy = 0.0, posz = 0.0;
				double velx = 0.0, vely = 0.0, velz = 0.0;

				file >> mass;
				file >> posx;
				file >> posy;
				file >> posz;
				file >> velx;
				file >> vely;
				file >> velz;

				Physics::Particle<double,Math::Vector3D<double>> p(
						mass,
						Math::Vector3D<double>( 0.0, 0.0, 0.0 ),
						Math::Vector3D<double>( 0.0, 0.0, 0.0 ),
						Math::Vector3D<double>( velx, vely, velz ),
						Math::Vector3D<double>( posx, posy, posz )
				);

	    		particles->push_back( p );
	    	}

	    	return particles;
	    }
	}

	std::list<Physics::Particle<double,Math::Vector3D<double>>>* InputFileReader::readModelFromFile( const char* filename ) {
		std::ifstream file( filename );
		if ( !file.is_open() ) {
			std::cerr << "could not open file" << std::endl;
			return 0L;
		} else {
			auto particles = new std::list<Physics::Particle<double,Math::Vector3D<double>>>();
			int snapshotId = 0;
			int particleCount = 0;
			double initialTime = 0.0;
			// snapshot (???)
			file >> snapshotId;
			// number of particles.
			file >> particleCount;
			// inital time (???)
			file >> initialTime;
			for( int i = 0; i < particleCount; ++i ) {
				double mass = 0.0;
				double posx = 0.0, posy = 0.0, posz = 0.0;
				double velx = 0.0, vely = 0.0, velz = 0.0;
				file >> mass;
				file >> posx;
				file >> posy;
				file >> posz;
				file >> velx;
				file >> vely;
				file >> velz;
				Physics::Particle<double,Math::Vector3D<double>> p(
						mass,
						Math::Vector3D<double>( 0.0, 0.0, 0.0 ),
						Math::Vector3D<double>( 0.0, 0.0, 0.0 ),
						Math::Vector3D<double>( velx, vely, velz ),
						Math::Vector3D<double>( posx, posy, posz )
				);
				particles->push_back( p );
			}
			return particles;
		}
	}

	std::list<Physics::Particle<double,Math::Vector3D<double>>>* InputFileReader::readFile( const char* filename ) {
		std::string file( filename );
		std::string filetype = file.substr( file.length() - 3, 3 );
		if( filetype.compare( "plm" ) == 0 ) {
			return this->readModelFromFile( filename );
		} else if( filetype.compare( "inp" ) == 0 ) {
			return this->createParticlesFromInputFile( filename );
		} else {
			std::cerr << "filetype not supported." << std::endl;
			return 0L;
		}
	}
}
