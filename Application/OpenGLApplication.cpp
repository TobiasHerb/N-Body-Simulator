/*
 * Application.cpp
 *
 *  Created on: May 16, 2012
 *      Author: Tobias Herb
 */

// includes.
#include "OpenGLApplication.h"
#include "../Renderer/SceneManager.h"

namespace Application {

	OpenGLApplication* OpenGLApplication::self = 0L;

	OpenGLApplication::OpenGLApplication( std::string name,
			 	 	      Math::Vector2D<int> position,
			 	 	      Math::Dimension2D<int> size ) {
		this->name = name;
		this->position = position;
		this->size = size;
		OpenGLApplication::self = (this);
	}

	OpenGLApplication::~OpenGLApplication() {
		if( this->sceneManager != 0L ) {
			delete this->sceneManager;
		}
	}

	const Math::Vector2D<int>& OpenGLApplication::getWindowCenter() const {
		return this->center;
	}

	const Math::Vector2D<int>& OpenGLApplication::getWindowPosition() const {
		return this->position;
	}

	const Math::Dimension2D<int>& OpenGLApplication::getWindowSize() const {
		return this->size;
	}

	void OpenGLApplication::setSceneManager( Renderer::SceneManager* sceneManager ) {
		this->sceneManager = sceneManager;
	}

	Renderer::SceneManager* OpenGLApplication::getSceneManager() const {
		return this->sceneManager;
	}

	void OpenGLApplication::initialize( int argc, char **argv ) {
		this->argc = argc;
		this->argv = argv;
		glutInit( &argc, argv );
		glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
		glutInitWindowPosition( this->position.X(), this->position.Y() );
		glutInitWindowSize( this->size.W(), this->size.H() );
		glutCreateWindow( this->name.c_str() );
		glutDisplayFunc( OpenGLApplication::static_manageScene );
		glutReshapeFunc( OpenGLApplication::static_changeWindowSize );
		glutIdleFunc( OpenGLApplication::static_manageScene );
		glutIgnoreKeyRepeat(1);
		glutKeyboardFunc( OpenGLApplication::static_processNormalKey );
		glutSpecialFunc( OpenGLApplication::static_pressKey );
		glutSpecialUpFunc( OpenGLApplication::static_releaseKey );
		glutMouseFunc( OpenGLApplication::static_mouseButton );
		glutMotionFunc( OpenGLApplication::static_mouseMove );
		this->initializeRenderContext();
	}

	void OpenGLApplication::manageScene() {
		this->processScene();
		this->sceneManager->renderScene();
	}

	void OpenGLApplication::run() {
		glutMainLoop();
	}

	void OpenGLApplication::shutdown() {
	}

	void OpenGLApplication::quitApplication() {
		exit( 0 );
	}

	void OpenGLApplication::initializeRenderContext() {
	}

	void OpenGLApplication::processScene() {
	}

	void OpenGLApplication::processNormalKey( unsigned char key, int x, int y ) {
	}

	void OpenGLApplication::pressKey( int key, int x, int y ) {
	}

	void OpenGLApplication::releaseKey( int key, int x, int y ) {
	}

	void OpenGLApplication::mouseMove( int x, int y ) {
	}

	void OpenGLApplication::mouseButton( int button, int state, int x, int y ) {
	}

	/**
	 * static wrapper functions for GLUT callbacks.
	 */

	void OpenGLApplication::static_manageScene() {
		OpenGLApplication::self->manageScene();
	}

	void OpenGLApplication::static_changeWindowSize( int width, int height ) {
		OpenGLApplication::self->sceneManager->changeWindowSize( width, height );
	}

	void OpenGLApplication::static_processNormalKey( unsigned char key, int x, int y ) {
		OpenGLApplication::self->processNormalKey( key, x, y );
	}

	void OpenGLApplication::static_pressKey( int key, int x, int y ) {
		OpenGLApplication::self->pressKey( key, x, y );
	}

	void OpenGLApplication::static_releaseKey( int key, int x, int y ) {
		OpenGLApplication::self->releaseKey( key, x, y );
	}

	void OpenGLApplication::static_mouseMove( int x, int y ) {
		OpenGLApplication::self->mouseMove( x, y );
	}

	void OpenGLApplication::static_mouseButton( int button, int state, int x, int y ) {
		OpenGLApplication::self->mouseButton( button, state, x, y );
	}
}
