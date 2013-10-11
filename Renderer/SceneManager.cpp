/*
 * SceneManager.cpp
 *
 *  Created on: May 30, 2012
 *      Author: Tobias Herb
 */

// includes.
#include "SceneManager.h"
#include "Camera.h"
#include "../Application/OpenGLApplication.h"

namespace Renderer {

	SceneManager::SceneManager( Application::OpenGLApplication*	app ) {
		this->app = app;
		camera = new Camera();
	}

	SceneManager::~SceneManager() {
		if( camera != 0L ) {
			delete camera;
		}
	}

	void SceneManager::changeWindowSize( int width, int height ) {
		if( height == 0 ) height = 1;
		app->size.set( width, height );
		app->center.set( width / 2, height / 2 );
		float ratio =  app->size.W() * 1.0 / app->size.H();
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glViewport( 0, 0, app->size.W(), app->size.H() );
		gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
		glMatrixMode( GL_MODELVIEW );
	}

	void SceneManager::renderScene() {
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glMatrixMode( GL_PROJECTION );
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D( 0.0, app->getWindowSize().W(), 0.0, app->getWindowSize().H() );
		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
		glLoadIdentity();
		this->render2D();
		glMatrixMode( GL_MODELVIEW );
		glPopMatrix();
		glMatrixMode( GL_PROJECTION );
		glPopMatrix();
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		this->camera->updateCamera();
		this->render3D();
		glutSwapBuffers();
	}
}
