#pragma once
#include "snowflake/core/core.h"
#include <string>
#include <unordered_map>

namespace SF {

	class Texture {

	private:
		static std::unordered_map<std::string, Ref<Texture>> s_Textures;

	protected:
		uint32_t m_ID;
		uint32_t m_Slot;
		uint32_t m_Width, m_Height;
		virtual void bind(const uint32_t slot) = 0;

	public:
		~Texture();

		uint32_t getID() { return this->m_ID; }
		uint32_t getSlot() { return this->m_Slot; }
		uint32_t getWidth() { return this->m_Width; };
		uint32_t getHeight() { return this->m_Height; }

		static void bind(const std::string& path, uint32_t slot) {

			s_Textures.find(path)->second->bind(slot);

		}

		static bool exists(const std::string& path) {

			return s_Textures.find(path) == s_Textures.end() ? false : true;

		}

		static int create(const std::string& path);

	};

}