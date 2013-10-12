/*
 * SceneManager.h
 *
 *  Created on: May 30, 2012
 *      Author: Tobias Herb
 */

#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

// forward declaration.
namespace Application {
	class OpenGLApplication;
}

namespace Renderer {

	// forward declaration.
	class Camera;

	class SceneManager {
	public:
		SceneManager( Application::OpenGLApplication* app );

		virtual ~SceneManager();

	private:
		friend class Application::OpenGLApplication;

	protected:
		Application::OpenGLApplication*		app;

		Camera*					camera;

	public:
		void renderScene();

		void changeWindowSize( int width, int height );

		inline Camera* getCamera() const {
			return camera;
		}

	protected:
		virtual void render2D() = 0;

		virtual void render3D() = 0;
	};
}

#endif /* SCENEMANAGER_H_ */
