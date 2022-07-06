#pragma once
#include "sceneObject.h"
#include "snowflake/renderer/camera.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>

namespace SF {

	class CameraObject : public SceneObject {
	private:
		CameraObject() {}
		OrthographicCameraController m_CameraController;

		//serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& boost::serialization::base_object<SceneObject>(*this);
			ar& m_CameraController;
		}

	public:
		CameraObject(OrthographicCameraController& cameracontroller) :m_CameraController(cameracontroller), SceneObject() {
			
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