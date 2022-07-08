#pragma once
#include "snowflake/core/core.h"
#include "renderable.h"
#include <glm.hpp>
#include <cereal/access.hpp>

namespace SF {

	class ColoredQuad : public Renderable {

	private:
		glm::vec4 m_Color;

		//serialization
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive& ar) {
			ar(cereal::base_class<Renderable>(this), CEREAL_NVP(m_Color));
		}


	public:
		ColoredQuad(glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3& size = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) :Renderable(position, size) {
			this->m_Type = RenderableType::COLORED_QUAD;
			this->m_Color = color;
		}
		~ColoredQuad() {}

		glm::vec4& getColor() {
			return m_Color;
		}

		void update() override {};

	};

}

CEREAL_REGISTER_TYPE(SF::ColoredQuad);