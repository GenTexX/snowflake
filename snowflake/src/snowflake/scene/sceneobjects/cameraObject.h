#pragma once
#include "sceneObject.h"
#include "snowflake/renderer/camera.h"

namespace SF {

	class CameraObject : public SceneObject {
	private:
		OrthographicCameraController m_CameraController;

	public:
		CameraObject(OrthographicCameraController& cameracontroller) :m_CameraController(cameracontroller){
			
			m_Type = SceneObjectType::CAMERA_OBJECT;
		
		}

		~CameraObject() {}

		//Position
		glm::vec3 getRelativePosition() override {
			return this->m_CameraController.getCamera().getPosition();
		}

		glm::vec3 getWorldPosition() override {
			return this->m_CameraController.getCamera().getPosition() + m_Parent->getWorldPosition();
		}

		void move(glm::vec3& direction) override {
			m_CameraController.move(direction);
		}

		//Camera
		OrthographicCamera& getCamera() {
			return m_CameraController.getCamera();
		}

	};

}