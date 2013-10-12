/*
 * Main.cpp
 *
 *  Created on: May 15, 2012
 *      Author: Tobias Herb
 */

#include "GlobalDefs.h"

// intern.
#include "Math/Vector2D.h"
#include "Math/Dimension2D.h"
#include "NBodySimulation/NBodyApplication.h"
#include "NBodySimulation/NBodySceneManager.h"
#include "Physics/PlummerModel/PlummerModelGenerator.h"
#include <iostream>

int main(int argc, char **argv) {

	//Physics::PlummerModelGenerator pmg;
	//pmg.generateModelAndWriteToFile( "plummer2.plm", 50 );

	Application::OpenGLApplication* app =
			new NBodySimulation::NBodyApplication( "Numerical N body simulation",
							       Math::Vector2D<int>( 100, 100 ),
							       Math::Dimension2D<int>( 800, 600 ) );

	// fake injection... for testing.
	if( argc != 2 ) {
		argc = 2;
		argv[0] = (char*)("NumerischeSimulation1");
		argv[1] = (char*)("3body_1.inp");//3body_1.inp
	}

	app->setSceneManager( new NBodySimulation::NBodySceneManager( app ) );
	app->initialize( argc, argv );
	app->run();
	app->shutdown();
	delete app;

	return 1;
}
