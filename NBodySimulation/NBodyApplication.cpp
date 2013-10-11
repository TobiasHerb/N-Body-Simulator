/*
 * NBodyApplication.cpp
 *
 *  Created on: May 16, 2012
 *      Author: Tobias Herb
 */

// includes.
#include "NBodyApplication.h"
#include "InputFileReader.h"
#include "NBodyIntegratorThread.h"
#include "../Renderer/SceneManager.h"
#include "../Renderer/Camera.h"
#include "../Physics/PlummerModel/PlummerModelGenerator.h"
#include <iostream>

namespace NBodySimulation {

	const static int MENU_ENTRY_STOP 			= 1;
	const static int MENU_ENTRY_PLAY 			= 2;
	const static int MENU_ENTRY_RESTART 		= 3;
	const static int MENU_ENTRY_SHOW_VECTORS	= 4;
	const static int MENU_ENTRY_SHOW_COM		= 5;
	const static int MENU_ENTRY_SHOW_TRACE 		= 6;

	const static std::string MENU_ENTRY_NAME_STOP 			= "Stop";
	const static std::string MENU_ENTRY_NAME_PLAY 			= "Play";
	const static std::string MENU_ENTRY_NAME_RESTART 		= "Restart";
	const static std::string MENU_ENTRY_NAME_SHOW_VECTORS 	= "Show Vectors";
	const static std::string MENU_ENTRY_NAME_SHOW_COM 		= "Show Center of Mass";
	const static std::string MENU_ENTRY_NAME_SHOW_TRACE 	= "Show Particle Trace";

	NBodyApplication::NBodyApplication( std::string name,
										Math::Vector2D<int> position,
										Math::Dimension2D<int> size ) :
										OpenGLApplication( name, position, size ) {
		this->simulationModel = new SimulationModel();
		this->fileReader = new InputFileReader( this->simulationModel );
	}

	NBodyApplication::~NBodyApplication() {
		if( this->simulationModel != 0L ) {
			delete this->simulationModel;
		}
		if( this->fileReader != 0L ) {
			delete this->fileReader;
		}
		NBodyIntegratorThread::releaseInstance();
	}

	void NBodyApplication::initialize( int argc, char** argv ) {
		OpenGLApplication::initialize( argc, argv );

		if( argc != 2 ) {
			std::cout << "usage: " << argv[0] << " <filename>\n" << std::endl;
			this->quitApplication();
		} else {
			//Math::Vector3D<double> zero;
			//Physics::Particle<double, Math::Vector3D<double> > smbh(1000000000.0, zero, zero, zero, zero);
			//Physics::PlummerModelGenerator pmg;
			//this->simulationModel->particles = pmg.generateModel( 100 );
			//this->simulationModel->particles->push_back(smbh);
			//this->simulationModel->particles = this->fileReader->createParticlesFromInputFile( argv[1] );
			this->simulationModel->particles = this->fileReader->readFile( argv[1] );
			this->simulationModel->initialParticles = new std::list<Physics::Particle<double,Math::Vector3D<double>>>( (*this->simulationModel->particles) );
			if( this->simulationModel->particles == 0L ) {
				std::cerr << "could not read input file." << std::endl;
				this->quitApplication();
			}
		}

		glutCreateMenu( NBodyApplication::static_menuHandler );
		glutAddMenuEntry( MENU_ENTRY_NAME_STOP.c_str(), MENU_ENTRY_STOP );
		glutAddMenuEntry( MENU_ENTRY_NAME_PLAY.c_str(), MENU_ENTRY_PLAY );
		glutAddMenuEntry( MENU_ENTRY_NAME_RESTART.c_str(), MENU_ENTRY_RESTART );
		glutAddMenuEntry( MENU_ENTRY_NAME_SHOW_VECTORS.c_str(), MENU_ENTRY_SHOW_VECTORS );
		glutAddMenuEntry( MENU_ENTRY_NAME_SHOW_COM.c_str(), MENU_ENTRY_SHOW_COM );
		glutAddMenuEntry( MENU_ENTRY_NAME_SHOW_TRACE.c_str(), MENU_ENTRY_SHOW_TRACE );
		glutAttachMenu( GLUT_RIGHT_BUTTON );

		time( &this->simulationModel->startTime );
		this->simulationModel->elapsedTime = 0;

		this->integratorThread = NBodyIntegratorThread::getInstance();
		this->integratorThread->setSimulationModel( this->simulationModel );
		this->integratorThread->execute( 0L );
	}

	void NBodyApplication::menuHandler( int value ) {
		switch( value ) {
			case MENU_ENTRY_STOP: {
				this->simulationModel->isSimulationRunning = false;
			} break;
			case MENU_ENTRY_PLAY: {
				this->simulationModel->isSimulationRunning = true;
			} break;
			case MENU_ENTRY_RESTART: {
				if( this->simulationModel->particles != 0L ) {
					delete this->simulationModel->particles;
				}
				this->simulationModel->particles = new std::list<Physics::Particle<double,Math::Vector3D<double>>>( (*this->simulationModel->initialParticles) );
				time( &this->simulationModel->startTime );
				this->simulationModel->isSimulationFinished = false;
				this->simulationModel->isSimulationRunning = true;
				this->integratorThread->execute( 0L );
			} break;
			case MENU_ENTRY_SHOW_VECTORS: {
				this->simulationModel->areVectorsShown = !simulationModel->areVectorsShown;
			} break;
			case MENU_ENTRY_SHOW_COM: {
				this->simulationModel->isCenterOfMassShown = !this->simulationModel->isCenterOfMassShown;
			} break;
			case MENU_ENTRY_SHOW_TRACE: {
				this->simulationModel->isTraceModeEnabled = !this->simulationModel->isTraceModeEnabled;
			} break;
		}
	}

	void NBodyApplication::static_menuHandler( int value ) {
		NBodyApplication* app = static_cast<NBodyApplication*>( OpenGLApplication::getSelfPtr() );
		app->menuHandler( value );
	}

	void NBodyApplication::processNormalKey( unsigned char key, int x, int y ) {
		switch( key ) {
			case 27: { 	this->quitApplication(); } break;
			case 'a': { this->sceneManager->getCamera()->moveForward( 0.1f ); } break;
			case 'y': { this->sceneManager->getCamera()->moveForward( -0.1f ); } break;
			case 'u': { this->sceneManager->getCamera()->rotateX( 1.0f ); } break;
			case 'd': { this->sceneManager->getCamera()->rotateX( -1.0f ); } break;
			case 'l': { this->sceneManager->getCamera()->rotateY( 1.0f ); } break;
			case 'r': { this->sceneManager->getCamera()->rotateY( -1.0f ); } break;
			case 's': { this->sceneManager->getCamera()->moveUpward( -1.0f ); } break;
			case 'x': { this->sceneManager->getCamera()->moveUpward( 1.0f ); } break;
			case 'q': { this->sceneManager->getCamera()->strafeRight( 1.0f ); } break;
			case 'w': { this->sceneManager->getCamera()->strafeRight( -1.0f ); } break;
			case 'c': {
				std::cout << "position vector: " << this->sceneManager->getCamera()->getPositionVector().toString() << std::endl;
				std::cout << "right vector:" << this->sceneManager->getCamera()->getRightVector().toString() << std::endl;
				std::cout << "up vector: " << this->sceneManager->getCamera()->getUpVector().toString() << std::endl;
				std::cout << "view vector" << this->sceneManager->getCamera()->getViewVector().toString() << std::endl;
			} break;
			case 'b': {
				this->simulationModel->integrationStepWidth = this->simulationModel->integrationStepWidth * (-1.0);
			} break;
			case 'p': {
				this->simulationModel->integrationStepWidth += 0.00001;
			} break;
			case 'o': {
				this->simulationModel->integrationStepWidth -= 0.00001;
			} break;
		}
	}

	void NBodyApplication::shutdown() {
		this->integratorThread->join();
	}
}
