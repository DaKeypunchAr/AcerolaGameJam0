#ifndef _OGL_TEXTURE_H
#define _OGL_TEXTURE_H

#include "GLEW/glew.h"
#include "glm/glm.hpp"
#include "../../Image/Image.h"

#include <string>

namespace OGL
{
	struct TextureFilters
	{
		unsigned int minFilter, magFilter, wrapS, wrapT;
		TextureFilters(unsigned int minFilter, unsigned int magFilter, unsigned int wrapS, unsigned int wrapT)
			: minFilter(minFilter), magFilter(magFilter), wrapS(wrapS), wrapT(wrapT) {}
		TextureFilters(unsigned int minMagFilter, unsigned wrapST)
			: minFilter(minMagFilter), magFilter(minMagFilter), wrapS(wrapST), wrapT(wrapST) {}
	};

	class Texture2D
	{
		public:
			Texture2D() = delete;
			Texture2D(const Texture2D& other) = delete;
			Texture2D(std::string imageLocation, TextureFilters filters, unsigned int imgChannels = 4);
			~Texture2D();

			void bind(unsigned int slot) const;

			void subImage(glm::ivec2 off, glm::ivec2 dim, unsigned char* img) const;

		private:
			glm::uvec2 m_TextureDimensions;
			unsigned int m_InternalFormat, m_Format;
			unsigned int m_ID;
	};
}

#endif