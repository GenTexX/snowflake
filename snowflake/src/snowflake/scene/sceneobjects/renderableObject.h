#pragma once
#include "sceneObject.h"
#include "../renderable.h"
#include "../coloredQuad.h"
#include "../texturedQuad.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>


namespace SF {

	class RenderableObject : public SceneObject {
	private:
		RenderableObject() {}
		Ref<Renderable> m_Renderable;

		//serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& boost::serialization::base_object<SceneObject>(*this);
			ar& m_Renderable;
		}
	
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