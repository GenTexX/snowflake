#pragma once
#include <glm.hpp>
#include "snowflake/renderer/texture.h"

namespace SF {

	enum class RenderableType {
		NONE = 0,
		COLORED_QUAD = 1,
		COLORED_CIRCLE = 2,
		TEXTURED_QUAD = 3
	};


	class Renderable {

	protected:
		glm::vec3 m_Position;
		glm::vec3 m_Size;
		RenderableType m_Type;

		Renderable(glm::vec3& position, glm::vec3& size) :m_Position(position), m_Size(size), m_Type(RenderableType::NONE) {}

	public:
		glm::vec3& getPosition() { return m_Position; }
		void setPosition(glm::vec3& position) { m_Position = position; }

		glm::vec3& getSize() { return m_Size; }
		void setSize(glm::vec3& size) { m_Size = size; }

		const RenderableType& type() {
			return m_Type;
		}

		~Renderable() {}

	};

	class ColoredQuad : public Renderable {

	private:
		glm::vec4 m_Color;


	public:
		ColoredQuad(glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3& size = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) :Renderable(position, size) {
			this->m_Type = RenderableType::COLORED_QUAD;
			this->m_Color = color;
		}
		~ColoredQuad() {}

	};

	class TexturedQuad : public Renderable {
	
	private:
		Ref<Texture> m_Texture;

	public:
		TexturedQuad(glm::vec3& position, glm::vec3& size, Ref<Texture> texture) :Renderable(position, size) {
			this->m_Type = RenderableType::TEXTURED_QUAD;
			m_Texture = texture;
		}

		Ref<Texture> getTexture() {
			return m_Texture;
		}

		~TexturedQuad() {}
	};

}