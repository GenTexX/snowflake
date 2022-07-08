#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <cereal/access.hpp>
#include <cereal/archives/portable_binary.hpp>

namespace SF {

	class OrthographicCamera {

	private:
		glm::vec3 m_Position;

		glm::mat4 m_Projection;
		glm::mat4 m_View;

		void recalculateView();

		//serialization
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive& ar) {
			ar(CEREAL_NVP(m_Position), CEREAL_NVP(m_Projection), CEREAL_NVP(m_View));
		}

	public:
		OrthographicCamera(float posX = 0.0f, float posY = 0.0f);
		OrthographicCamera(glm::vec3& position);
		~OrthographicCamera();

		float& getPosX();
		float& getPosY();
		glm::vec3& getPosition();

		void setPosX(float posX);
		void setPosY(float posY);

		void setPosition(glm::vec3& position);

		void addPosX(float distanceX);
		void addPosY(float distanceY);

		void addPosition(glm::vec3& add);

		glm::mat4& getViewMatrix() { 
			return this->m_View; 
		}
		glm::mat4& getProjectionMatrix() { return this->m_Projection; }

	};

	class OrthographicCameraController {

	private:
		OrthographicCamera m_Camera;

		//serialization
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive& ar) {
			ar(CEREAL_NVP(m_Camera));
		}

	public:
		OrthographicCameraController(float posX = 0.0f, float posY = 0.0f);
		~OrthographicCameraController();

		void moveX(float distance = 0.1f);
		void moveY(float distance = 0.1f);
		void move(glm::vec3& direction);

		OrthographicCamera& getCamera() { return this->m_Camera; }

	};

}