#pragma once
#include "snowflake/core/core.h"
#include "renderable.h"
#include <glm.hpp>
#include <cereal/access.hpp>
#include <cereal/types/string.hpp>

namespace SF {

	class TexturedQuad : public Renderable {

	private:
		TexturedQuad() {}
		std::string m_Texture;

		//serialization
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive& ar) {
			ar(cereal::base_class<Renderable>(this), CEREAL_NVP(m_Texture));
		}

	public:
		TexturedQuad(glm::vec3& position, glm::vec3& size, const std::string& texture) : Renderable(position, size) {
			this->m_Type = RenderableType::TEXTURED_QUAD;
			m_Texture = texture;
		}
		~TexturedQuad() {}

		const std::string& getTexture() {
			return m_Texture;
		}

		void update() override {};

	};

}

CEREAL_REGISTER_TYPE(SF::TexturedQuad);