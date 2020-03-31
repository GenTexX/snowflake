#include "sfpch.h"
#include <GL/glew.h>
#include "openGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace SF {

	OpenGLTexture::OpenGLTexture(const std::string& path) {

		int width, height, channels;

		stbi_set_flip_vertically_on_load(true);		//flips the image vertically... opengl-stuff blabla
		
		unsigned char* data = nullptr;

		data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		SF_ASSERT(data, "Failed to load Image!");

		this->m_Width = width;
		this->m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;

		switch (channels)
		{
		case STBI_grey:
			break;
		case STBI_grey_alpha:
			break;
		case STBI_rgb:
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
			break;
		case STBI_rgb_alpha:
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
			break;

		default:
			break;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &(this->m_ID));
		glTextureStorage2D(this->m_ID, 1, internalFormat, this->m_Width, this->m_Height);

		glTextureParameteri(this->m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(this->m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(this->m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(this->m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(this->m_ID, 0, 0, 0, this->m_Width, this->m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

	}

	OpenGLTexture::~OpenGLTexture() {

		glDeleteTextures(1, &(this->m_ID));

	}

	void OpenGLTexture::bind(const uint32_t slot) {
	
		this->m_Slot = slot;
		glBindTextureUnit(slot, this->m_ID);
	
	}

}
