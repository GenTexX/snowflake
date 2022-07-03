#pragma once
#include "sceneObject.h"
#include <initializer_list>
#include "../renderable.h"


namespace SF {

	class RenderableObject : public SceneObject {
	private:
		Ref<Renderable> m_Renderable;
	
	public:
		RenderableObject(Ref<Renderable> renderable) :m_Renderable(renderable) {
			m_Type = SceneObjectType::RENDERABLE_OBJECT;
		}
		~RenderableObject() {}
		
		//Position
		glm::vec3 getRelativePosition() override {
			return this->m_Renderable->getPosition();
		}

		glm::vec3 getWorldPosition() override {
			if (m_Parent == nullptr) 
				return getRelativePosition();
			
			return this->m_Renderable->getPosition() + m_Parent->getWorldPosition();
		}

		void move(glm::vec3& direction) override {
			m_Renderable->setPosition(m_Renderable->getPosition() + direction);
		}

		//Renderable
		Renderable& getRenderable() {
			return *m_Renderable;
		}


	};

}