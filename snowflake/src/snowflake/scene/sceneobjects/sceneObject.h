#pragma once
#include "../renderable.h"
#include "snowflake/core/core.h"
#include <list>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>

namespace SF {
	enum class SceneObjectType {
		EMPTY = 0,
		CAMERA_OBJECT = 1,
		LIGHT_OBJECT = 2,
		RENDERABLE_OBJECT = 3
	};

	class SceneObject {
	protected:
		SceneObject* m_Parent;
		std::list<Ref<SceneObject>> m_Childs;
		SceneObjectType m_Type;
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& m_Parent;
			ar& m_Childs;
			ar& m_Type;
		}

	public:
		SceneObject();
		~SceneObject();

		void addChild(Ref<SceneObject> child);
		void removeChild(Ref<SceneObject> child);

		virtual void update() = 0;

		virtual glm::vec3 getRelativePosition() = 0;
		virtual glm::vec3 getWorldPosition() = 0;
		virtual void move(glm::vec3& direction) = 0;

		const SceneObjectType type() {
			return m_Type;
		}

	};
}
