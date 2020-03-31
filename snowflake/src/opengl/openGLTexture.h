#pragma once

#include "snowflake/renderer/texture.h"

namespace SF {

	class OpenGLTexture : public Texture {

	public:
		OpenGLTexture(const std::string& path);
		~OpenGLTexture();

		virtual void bind(uint32_t slot = 0) override;

	};

}