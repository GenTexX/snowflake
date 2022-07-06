#pragma once
#include <glm.hpp>
#include "snowflake/renderer/texture.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/base_object.hpp>

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
		Renderable() { m_Position = glm::vec3(); m_Size = glm::vec3(); m_Type = RenderableType::NONE; }
		Renderable(glm::vec3& position, glm::vec3& size) :m_Position(position), m_Size(size), m_Type(RenderableType::NONE) {}

	private:
		//serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& m_Position;
			ar& m_Size;
			ar& m_Type;
		}

	public:
		glm::vec3& getPosition() { return m_Position; }
		void setPosition(glm::vec3& position) { m_Position = position; }

		glm::vec3& getSize() { return m_Size; }
		void setSize(glm::vec3& size) { m_Size = size; }

		const RenderableType& type() {
			return m_Type;
		}

		virtual void update() = 0;

		~Renderable() {}

	};

}