/*
 * NBodySceneManager.h
 *
 *  Created on: May 30, 2012
 *      Author: Tobias Herb
 */

#ifndef NBODYSCENEMANAGER_H_
#define NBODYSCENEMANAGER_H_

// includes.
#include "../Renderer/SceneManager.h"
#include "../NBodySimulation/NBodyApplication.h"

// forward declaration.
namespace Application {
	class OpenGLApplication;
}

namespace NBodySimulation {

	class NBodySceneManager : public Renderer::SceneManager {
	public:
		NBodySceneManager( Application::OpenGLApplication* app );

		virtual ~NBodySceneManager();

	private:
		friend class NBodySimulation::NBodyApplication;

		NBodySimulation::NBodyApplication*	nBodyApp;

		NBodySimulation::NBodyApplication::SimulationModel*	simulationModel;

	public:
		void render2D();

		void render3D();

	private:
		void drawNet( float size, int lx, int lz );

		void drawArrow( Math::Vector3D<double> s, Math::Vector3D<double> d );

		void drawString( const float x, const float y, std::string text );

		void drawLine( Math::Vector3D<double> a, Math::Vector3D<double> b );
	};
}

#endif /* NBODYSCENEMANAGER_H_ */
