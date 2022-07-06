#pragma once
#include "snowflake/core/core.h"
#include "renderable.h"
#include <glm.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>

namespace SF {

	class TexturedQuad : public Renderable {

	private:
		TexturedQuad() {}
		std::string m_Texture;

		//serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& boost::serialization::base_object<Renderable>(*this);
			ar& m_Texture;
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