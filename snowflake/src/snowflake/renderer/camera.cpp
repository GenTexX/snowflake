#include "sfpch.h"
#include "camera.h"

namespace SF {
	void OrthographicCamera::recalculateView() {

		this->m_View = glm::inverse(glm::translate(glm::mat4(1.0f), this->m_Position));

	}
	OrthographicCamera::OrthographicCamera(float posX, float posY) {

		this->m_Position.x = posX;
		this->m_Position.y = posY;
		this->m_Position.z = 1.0f;

		this->m_Projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f);

		this->recalculateView();

	}

	OrthographicCamera::OrthographicCamera(glm::vec3& position) {

		this->m_Position = position;
		
		this->m_Projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f);
		
		this->recalculateView();

	}

	OrthographicCamera::~OrthographicCamera() {



	}

	float& OrthographicCamera::getPosX()
	{
		return this->m_Position.x;
	}

	float& OrthographicCamera::getPosY()
	{
		return this->m_Position.y;
	}

	glm::vec3& OrthographicCamera::getPosition() {

		return this->m_Position;

	}

	void OrthographicCamera::setPosX(float posX) {

		this->m_Position.x = posX;
		this->recalculateView();

	}

	void OrthographicCamera::setPosY(float posY) {

		this->m_Position.y = posY;
		this->recalculateView();

	}

	void OrthographicCamera::setPosition(glm::vec3& position) {

		this->m_Position += position;
		this->recalculateView();

	}

	void OrthographicCamera::addPosX(float distanceX) {

		this->m_Position.x += distanceX;
		this->recalculateView();

	}

	void OrthographicCamera::addPosY(float distanceY) {

		this->m_Position.y += distanceY;
		this->recalculateView();

	}

	void OrthographicCamera::addPosition(glm::vec3& add) {

		this->m_Position += add;
		this->recalculateView();

	}

	OrthographicCameraController::OrthographicCameraController(float posX, float posY) : m_Camera(posX, posY){



	}

	OrthographicCameraController::~OrthographicCameraController() {



	}

	void OrthographicCameraController::moveX(float distance) {

		this->m_Camera.addPosX(distance);

	}

	void OrthographicCameraController::moveY(float distance) {

		this->m_Camera.addPosY(distance);

	}

	void OrthographicCameraController::move(glm::vec3& direction) {

		this->m_Camera.addPosition(direction);

	}

}