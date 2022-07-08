#pragma once
#include "sceneObject.h"
#include "snowflake/renderer/camera.h"
#include <cereal/access.hpp>
#include <cereal/types/memory.hpp>

namespace SF {

	class CameraObject : public SceneObject {
	private:
		CameraObject() {}
		OrthographicCameraController m_CameraController;

		//serialization
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive& ar) {
			ar(cereal::base_class<SceneObject>(this), CEREAL_NVP(m_CameraController));
		}

	public:
		CameraObject(OrthographicCameraController& cameracontroller) :m_CameraController(cameracontroller), SceneObject() {

			m_Type = SceneObjectType::CAMERA_OBJECT;

		}

		~CameraObject() {}

		void update() override {

		}

		//Position
		glm::vec3 getRelativePosition() override {
			return this->m_CameraController.getCamera().getPosition();
		}

		glm::vec3 getWorldPosition() override {

			if (m_Parent.expired()) {
				return getRelativePosition();
			}

			return this->m_CameraController.getCamera().getPosition() + m_Parent.lock()->getWorldPosition();
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

CEREAL_REGISTER_TYPE(SF::CameraObject);