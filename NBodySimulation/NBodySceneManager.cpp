/*
 * NBodySceneManager.cpp
 *
 *  Created on: May 30, 2012
 *      Author: Tobias Herb
 */

// includes.
#include "../GlobalDefs.h"
#include "NBodySceneManager.h"
#include "NBodyIntegratorThread.h"
#include "../Renderer/Camera.h"
#include <iostream>
#include "../Physics/IntegratorFactory.h"

namespace NBodySimulation {

	NBodySceneManager::NBodySceneManager( Application::OpenGLApplication* app )
		: SceneManager( app ) {
		nBodyApp = static_cast<NBodySimulation::NBodyApplication*>( app );
		this->simulationModel = nBodyApp->getSimulationModel();

		camera->setCamera( Math::Vector3D<float>( 0.0f, -0.515038f, -0.857168f ),
						   Math::Vector3D<float>( 1.0f, 0.0f, 0.0f ),
						   Math::Vector3D<float>( -0.0f, 0.857168f, -0.515038f ),
						   Math::Vector3D<float>( 0.0f, 8.61805f, 11.4286f ) );

		/*camera->setCamera( Math::Vector3D<float>( 0, -0.515038, -0.857168 ),
						   Math::Vector3D<float>( 1.0f, 0.0f, 0.0f ),
						   Math::Vector3D<float>( -0, 0.857168, -0.515038 ),
						   Math::Vector3D<float>( 0, 30.3013, 47.5152 ) );*/
	}

	NBodySceneManager::~NBodySceneManager() {
	}

	void NBodySceneManager::render2D() {
		std::stringstream ssKineticEnergy;
		ssKineticEnergy << "kinetic energy: " << this->simulationModel->kineticEnergy;
		std::stringstream ssPotentialEnergy;
		ssPotentialEnergy << "potential energy: " << this->simulationModel->potentialEnergy;
		std::stringstream ssTotalEnergy;
		ssTotalEnergy << "total energy: " << this->simulationModel->totalEnergy;

		glColor3f( 0.0, 1.0, 0.0 );
		drawString( 10, app->getWindowSize().H() - 15, ssKineticEnergy.str() );
		drawString( 10, app->getWindowSize().H() - 30, ssPotentialEnergy.str() );
		drawString( 10, app->getWindowSize().H() - 45, ssTotalEnergy.str() );

		std::stringstream ssElapsedTime;
		ssElapsedTime << "elapsed time: " << this->simulationModel->elapsedTime << "s";
		drawString( app->getWindowSize().W() - 180, app->getWindowSize().H() - 15, ssElapsedTime.str() );

		std::stringstream ssSystemTime;
		ssSystemTime << "system time: " << this->simulationModel->systemTime << "s";
		drawString( app->getWindowSize().W() - 220, app->getWindowSize().H() - 30, ssSystemTime.str() );

		if( this->simulationModel->integratorType == Physics::INTEGRATOR_LEAPFROG ) {
			std::stringstream ssIntegrationStepWidth;
			ssIntegrationStepWidth << "integration step width: " << this->simulationModel->integrationStepWidth;
			drawString( app->getWindowSize().W() - 500, app->getWindowSize().H() - 15, ssIntegrationStepWidth.str() );
			if( this->simulationModel->integrationStepWidth > 0 ) {
				drawString( app->getWindowSize().W() - 500, app->getWindowSize().H() - 30, "press <b> for reversed time" );
			} else {
				drawString( app->getWindowSize().W() - 500, app->getWindowSize().H() - 30, "press <b> for forward time" );
			}
			drawString( app->getWindowSize().W() - 500, app->getWindowSize().H() - 45, "press <p> increase integration step width" );
			drawString( app->getWindowSize().W() - 500, app->getWindowSize().H() - 60, "press <o> decrease integration step width" );
		}

		if( this->simulationModel->isSimulationFinished ) {
			std::stringstream ssEnergyError;
			ssEnergyError << "energy error: " << (this->simulationModel->totalEnergyStartup - this->simulationModel->totalEnergy);
			drawString( 15, 15, ssEnergyError.str() );
		}

		std::stringstream ssIntegrator;
		switch( this->simulationModel->integratorType ) {
			case Physics::INTEGRATOR_LEAPFROG: {
				ssIntegrator << "Leapfrog Integrator";
			} break;
			case Physics::INTEGRATOR_HERMITE: {
				ssIntegrator << "Hermite Integrator";
			} break;
		}

		drawString( app->getWindowSize().W() - 200, 15, ssIntegrator.str() );
	}

	void NBodySceneManager::render3D() {
		glScalef( 3.0, 1.0, 3.0 );
		glColor3f( 0.3, 0.3, 0.3 );
		glPushMatrix();
			glTranslatef( 0.0, -5.0, 0.0 );
			drawNet( 10.0, 30, 30 );
		glPopMatrix();

		nBodyApp->getIntegratorThread()->lock();
		for( Physics::Particle<double,Math::Vector3D<double>>& p :
				(*this->simulationModel->particles) ) {

			if( this->simulationModel->areVectorsShown ) {
				glColor3f( 0.0f, 1.0f, 0.0f );
				drawArrow( p.getPosition(), p.getVelocity() );
				glColor3f( 0.0f, 0.0f, 1.0f );
				drawArrow( p.getPosition(), p.getAcceleration() );
			}

			if( this->simulationModel->isCenterOfMassShown ) {
				glColor3f( 1.0f, 0.0f, 0.0f );
				drawLine( this->simulationModel->centerOfMassPosition, p.getPosition() );
			}

			glPushMatrix();
			glColor3f( 1.0, 1.0, 1.0 );
			glTranslatef( p.getPosition().X(),
						  p.getPosition().Y(),
						  p.getPosition().Z() );
			glutSolidSphere( 0.03f , 10, 10 );
			glPopMatrix();

			if( this->simulationModel->particles->size() <= 10 ) {
				if( this->simulationModel->isSimulationRunning ) {
					p.addTraceElement( p.getPosition() );
				}
				if( this->simulationModel->isTraceModeEnabled ) {
					glPushMatrix();
					glColor3f( 0.0, 0.8, 0.0 );
					glBegin(GL_POINTS);
					for( Math::Vector3D<double>& v : p.getParticleTrace() ) {
						glVertex3f( v.X(), v.Y(), v.Z() );
					}
					glEnd( );
					glPopMatrix();
				}
			}
		}

		if( this->simulationModel->isCenterOfMassShown ) {
			glPushMatrix();
			glColor3f( 0.0, 1.0, 0.0 );
			glTranslatef( this->simulationModel->centerOfMassPosition.X(),
						  this->simulationModel->centerOfMassPosition.Y(),
						  this->simulationModel->centerOfMassPosition.Z() );
			glutSolidSphere( 0.03f , 10, 10 );
			glPopMatrix();
		}

		nBodyApp->getIntegratorThread()->unlock();
	}

	void NBodySceneManager::drawNet( float size, int lx, int lz ) {
		glBegin( GL_LINES );
		for( int xc = 0; xc < lx; xc++ ) {
			glVertex3f(	-size / 2.0 + xc / (float)(lx - 1) * size, 0.0, size / 2.0 );
			glVertex3f(	-size / 2.0 + xc / (float)(lx - 1) * size, 0.0, size / -2.0);
		}
		for( int zc = 0; zc < lz; zc++ ) {
			glVertex3f(	size / 2.0, 0.0, -size / 2.0 + zc / (float)(lz - 1) * size );
			glVertex3f(	size / -2.0, 0.0, -size / 2.0 + zc / (float)(lz - 1) * size );
		}
		glEnd();
	}

	void NBodySceneManager::drawArrow( Math::Vector3D<double> s, Math::Vector3D<double> d ) {
		Math::Vector3D<double> v = ( s + ( d.normalize() / 2 ) );
		glBegin( GL_LINES );
			glVertex3f(	s.X(), s.Y(), s.Z() );
			glVertex3f(	v.X(), v.Y(), v.Z() );
		glEnd();
	}

	void NBodySceneManager::drawString( const float x, const float y, std::string text ) {
		glRasterPos2i( x, y );
		for( std::string::iterator iter = text.begin(); iter != text.end(); ++iter ) {
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, (*iter) );
		}
	}

	void NBodySceneManager::drawLine( Math::Vector3D<double> a, Math::Vector3D<double> b ) {
		glBegin( GL_LINES );
			glVertex3f(	a.X(), a.Y(), a.Z() );
			glVertex3f(	b.X(), b.Y(), b.Z() );
		glEnd();
	}
}
