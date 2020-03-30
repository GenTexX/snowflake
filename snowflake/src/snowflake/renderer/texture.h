#pragma once
#include "snowflake/core/core.h"

namespace SF {

	class Texture {

	protected:
		uint32_t m_ID;
		uint32_t m_Slot;
		uint32_t m_Width, m_Height;

	public:
		~Texture();

		uint32_t getID() { return this->m_ID; }
		uint32_t getSlot() { return this->m_Slot; }
		uint32_t getWidth() { return this->m_Width; };
		uint32_t getHeight() { return this->m_Height; }

		virtual void bind(const uint32_t slot = 0) = 0;

		static Ref<Texture> create(const std::string& path);

	};

}