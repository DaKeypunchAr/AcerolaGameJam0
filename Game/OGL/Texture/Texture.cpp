#include "Texture.h"

#include <iostream>

namespace OGL
{
	Texture2D::Texture2D(std::string imageLocation, TextureFilters filters, unsigned int channels)
	{
		initialize(imageLocation, filters, channels);
	}
	Texture2D::Texture2D(glm::uvec2 preservedDimension, TextureFilters filters, unsigned int channels)
	{
		initialize(preservedDimension, filters, channels);
	}
	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	void Texture2D::bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, m_ID);
	}
	void Texture2D::subImage(glm::ivec2 off, glm::ivec2 dim, unsigned char* img) const
	{
		switch (m_Format)
		{
			case GL_RED:
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				break;
			case GL_RG:
				glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
				break;
			case GL_RGB:
				glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
				break;
			case GL_RGBA:
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
				break;
		}

		glTextureSubImage2D(m_ID, 0, off.x, off.y, dim.x, dim.y, m_Format, GL_UNSIGNED_BYTE, img);
	}

	void Texture2D::initialize(std::string imageLocation, TextureFilters filters, unsigned int channels)
	{
		switch (channels)
		{
		case 1:
			m_InternalFormat = GL_R8;
			m_Format = GL_RED;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			break;
		case 2:
			m_InternalFormat = GL_RG8;
			m_Format = GL_RG;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
			break;
		case 3:
			m_InternalFormat = GL_RGB8;
			m_Format = GL_RGB;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
			break;
		case 4:
			m_InternalFormat = GL_RGBA8;
			m_Format = GL_RGBA;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			break;
		default:
			std::cerr << "Invalid num of channels!\n";
			__debugbreak();
		}

		stbi_set_flip_vertically_on_load(true);
		int w, h;
		unsigned char* img = stbi_load(imageLocation.c_str(), &w, &h, nullptr, channels);
		m_TextureDimensions = { w, h };

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		glTextureStorage2D(m_ID, 1, m_InternalFormat, m_TextureDimensions.x, m_TextureDimensions.y);
		subImage({ 0, 0 }, m_TextureDimensions, img);

		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, filters.minFilter);
		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, filters.magFilter);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, filters.wrapS);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, filters.wrapT);

		stbi_image_free(img);
	}
	void Texture2D::initialize(glm::uvec2 preservedDimension, TextureFilters filters, unsigned int channels)
	{
		switch (channels)
		{
		case 1:
			m_InternalFormat = GL_R8;
			m_Format = GL_RED;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			break;
		case 2:
			m_InternalFormat = GL_RG8;
			m_Format = GL_RG;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
			break;
		case 3:
			m_InternalFormat = GL_RGB8;
			m_Format = GL_RGB;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
			break;
		case 4:
			m_InternalFormat = GL_RGBA8;
			m_Format = GL_RGBA;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			break;
		default:
			std::cerr << "Invalid num of channels!\n";
			__debugbreak();
		}

		m_TextureDimensions = preservedDimension;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		glTextureStorage2D(m_ID, 1, m_InternalFormat, m_TextureDimensions.x, m_TextureDimensions.y);

		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, filters.minFilter);
		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, filters.magFilter);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, filters.wrapS);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, filters.wrapT);
	}
}