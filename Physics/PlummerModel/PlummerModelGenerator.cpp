/*
 * PlummerModelGenerator.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: Tobias Herb
 */

// includes.
#include "../CommonPhysics.h"
#include "PlummerModelGenerator.h"
#include "../../Math/CommonMath.h"
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <fstream>

namespace Physics {

	PlummerModelGenerator::PlummerModelGenerator() {
	}

	PlummerModelGenerator::~PlummerModelGenerator() {
	}

	std::list<Particle<double,Math::Vector3D<double>>>* PlummerModelGenerator::generateModel( int particleCount ) {
		// sanity check.
		assert( particleCount > 0 );
		auto* particles = new std::list<Particle<double,Math::Vector3D<double>>>();

		double M = 1.0;
		srand( time( 0L ) );
		int N = particleCount;
		double m = M / N;

		double E = -0.25;

		double E1 = -4 * E;

		double radiusScaling = ( 3 * Math::CommonMath::PI / 64 ) * pow( abs( E1 ), -1 );

		double velocityScaling = pow( ( 64 / 3 * Math::CommonMath::PI ), 0.5 ) * pow( abs( E1 ), 0.5 );

		for( int i = 0; i < N; ++i ) {

			double x1 = ( rand() % 100 ) / 100.0;
			double r = pow( ( pow( x1, -(2.0 / 3.0) ) - 1 ), -0.5 );
			double x2 = ( rand() % 100 ) / 100.0;
			double x3 = ( rand() % 100 ) / 100.0;
			double z = ( 1 - 2 * x2 ) * r;
			double x = pow( ( ( r * r ) - ( z * z ) ), 0.5 ) * cos( 2 * Math::CommonMath::PI * x3 );
			double y = pow( ( ( r * r ) - ( z * z ) ), 0.5 ) * sin( 2 * Math::CommonMath::PI * x3 );
			double ve = pow( 2, 0.5 ) * pow( (1 + ( r * r ) ), -(1.0 / 4.0) );
			double x4 = 0.0;
			double x5 = 0.0;

			do {
				x4 = ( rand() % 100 ) / 100.0;
				x5 = ( rand() % 100 ) / 100.0;
			} while( 0.1 * x5 >= ( x4 * x4 ) * pow( ( 1 - ( x4 * x4 ) ), (7.0 / 2.0) ) );

			double V = x4 * ve;
			double x6 = ( rand() % 100 ) / 100.0;
			double x7 = ( rand() % 100 ) / 100.0;

			double w = ( 1 - 2 * x6 ) * V;
			double u = pow( ( ( V * V ) - ( w * w ) ), 0.5 ) * cos( Math::CommonMath::PI * 2 * x7 );
			double v = pow( ( ( V * V ) - ( w * w ) ), 0.5 ) * sin( Math::CommonMath::PI * 2 * x7 );

			x *= radiusScaling;
			y *= radiusScaling;
			z *= radiusScaling;

			u *= velocityScaling;
			v *= velocityScaling;
			w *= velocityScaling;

			Particle<double, Math::Vector3D<double>> p( m, Math::Vector3D<double>( 0.0, 0.0, 0.0 ),
														   Math::Vector3D<double>( 0.0, 0.0, 0.0 ),
														   Math::Vector3D<double>( u, v, w ),
														   Math::Vector3D<double>( x, y, z ) );
			particles->push_back( p );
		}
		return particles;
	}

	void PlummerModelGenerator::generateModelAndWriteToFile( const char* filename, int particleCount ) {
		// sanity check.
		assert( filename != 0L );
		assert( particleCount > 0 );
		std::list<Particle<double,Math::Vector3D<double>>>* particles = this->generateModel( particleCount );
		std::ofstream file( filename );
		// snapshot (???)
		file << 0 << std::endl;
		// number of particles.
		file << particleCount << std::endl;
		// inital time (???)
		file << 0.0 << std::endl;
		for( Physics::Particle<double,Math::Vector3D<double>> p : (*particles) ) {
			file << p.getMass() << std::endl;
			file << p.getPosition().X() << std::endl;
			file << p.getPosition().Y() << std::endl;
			file << p.getPosition().Z() << std::endl;
			file << p.getVelocity().X() << std::endl;
			file << p.getVelocity().Y() << std::endl;
			file << p.getVelocity().Z() << std::endl;
		}
		delete particles;
	}
}
