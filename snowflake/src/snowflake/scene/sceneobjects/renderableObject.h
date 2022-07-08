#pragma once
#include "sceneObject.h"
#include "../renderable.h"
#include "../coloredQuad.h"
#include "../texturedQuad.h"
#include <memory>
#include <cereal/access.hpp>
#include <cereal/types/memory.hpp>


namespace SF {

	class RenderableObject : public SceneObject {
	private:
		RenderableObject() {}
		Ref<Renderable> m_Renderable;

		//serialization
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive& ar) {
			ar(cereal::base_class<SceneObject>(this), CEREAL_NVP(m_Renderable));
		}
	
	public:
		RenderableObject(Ref<Renderable> renderable) :m_Renderable(renderable) {
			m_Type = SceneObjectType::RENDERABLE_OBJECT;
		}
		~RenderableObject() {}
		
		void update() override {}

		//Position
		glm::vec3 getRelativePosition() override {
			return this->m_Renderable->getPosition();
		}

		glm::vec3 getWorldPosition() override {
			if (m_Parent.expired()) 
				return getRelativePosition();
			
			return this->m_Renderable->getPosition() + m_Parent.lock()->getWorldPosition();
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

CEREAL_REGISTER_TYPE(SF::RenderableObject);