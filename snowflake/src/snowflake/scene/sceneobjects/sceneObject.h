#pragma once
#include "../renderable.h"
#include "snowflake/core/core.h"
#include <list>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/memory.hpp>

namespace SF {
	enum class SceneObjectType {
		EMPTY = 0,
		CAMERA_OBJECT = 1,
		LIGHT_OBJECT = 2,
		RENDERABLE_OBJECT = 3
	};

	class SceneObject : public std::enable_shared_from_this<SceneObject> {
	protected:
		std::weak_ptr<SceneObject> m_Parent;
		std::list<Ref<SceneObject>> m_Childs;
		SceneObjectType m_Type;
	private:
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive& ar) {
			ar(CEREAL_NVP(m_Parent), CEREAL_NVP(m_Childs), CEREAL_NVP(m_Type));
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
