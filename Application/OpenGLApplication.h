/*
 * Application.h
 *
 *  Created on: May 16, 2012
 *      Author: Tobias Herb
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "../GlobalDefs.h"

// includes.
#include "../Math/Dimension2D.h"
#include "../Math/Vector2D.h"
#include <string>

//opengl.
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

// forward declaration.
namespace Renderer {
	class SceneManager;
}

namespace Application {

	class OpenGLApplication {
	public:
		OpenGLApplication( std::string name,
				   Math::Vector2D<int> position,
				   Math::Dimension2D<int> size );

		virtual ~OpenGLApplication();

	private:
		friend class Renderer::SceneManager;

		Math::Vector2D<int>		center;

		Math::Vector2D<int>		position;

		Math::Dimension2D<int>		size;

		std::string 			name;

		int 				argc;

		char**				argv;

	protected:
		Renderer::SceneManager*	sceneManager;

	public:
		void setSceneManager( Renderer::SceneManager* sceneManager );

		Renderer::SceneManager* getSceneManager() const;

		const Math::Vector2D<int>& getWindowCenter() const;

		const Math::Vector2D<int>& getWindowPosition() const;

		const Math::Dimension2D<int>& getWindowSize() const;

		virtual void initialize( int argc, char **argv );

		void run();

		virtual void shutdown();

		virtual void quitApplication();

		inline int getArgumentCount() const { return argc; }

		inline char** getArguments() const { return argv; }

	protected:
		virtual void initializeRenderContext();

		virtual void processScene();

		virtual void processNormalKey( unsigned char key, int x, int y );

		virtual void pressKey( int key, int x, int y );

		virtual void releaseKey( int key, int x, int y );

		virtual void mouseMove( int x, int y );

		virtual void mouseButton( int button, int state, int x, int y );

	private:
		void manageScene();

	private:
		static OpenGLApplication* self;

		static void static_manageScene();

		static void static_changeWindowSize( int width, int height );

		static void static_processNormalKey( unsigned char key, int x, int y );

		static void static_pressKey( int key, int x, int y );

		static void static_releaseKey( int key, int x, int y );

		static void static_mouseMove( int x, int y );

		static void static_mouseButton( int button, int state, int x, int y );

	public:
		static OpenGLApplication* getSelfPtr() {
			return self;
		}
	};
}

#endif /* APPLICATION_H_ */
