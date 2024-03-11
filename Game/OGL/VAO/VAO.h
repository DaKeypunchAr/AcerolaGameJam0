#ifndef _OGL_VAO_H
#define _OGL_VAO_H

#include "GLEW/glew.h"

#include <vector>

namespace OGL
{
	struct AttribInfo
	{
		unsigned int attribIdx;
		unsigned int count;
		unsigned int offset;

		AttribInfo(unsigned int attribIdx, unsigned int count, unsigned int offset)
			: attribIdx(attribIdx), count(count), offset(offset) {}
	};

	struct VBOInfo
	{
		unsigned int bindingIdx;
		unsigned int usage;
		unsigned int stride;
		std::vector<AttribInfo> attribs;

		VBOInfo(unsigned int bindingIdx, unsigned int usage, unsigned int stride, std::vector<AttribInfo> attribs)
			: bindingIdx(bindingIdx), usage(usage), stride(stride), attribs(attribs) {}
	};

	class VAO
	{
		public:
			VAO() = default;
			VAO(const VAO& other) = delete;
			VAO(unsigned int ebCount, std::vector<unsigned int> vbCounts, std::vector<VBOInfo> vboInfos);
			~VAO();

			void bind() const;

			void updateVB(unsigned int off, std::vector<float> buffer, unsigned int bindingIdx) const;
			void updateEB(unsigned int off, std::vector<unsigned int> buffer) const;

			void recreateVB(unsigned int vbCount, unsigned int usage, unsigned int bindingIdx) const;
			void recreateEB(unsigned int ebCount, unsigned int usage) const;

			void initialize(unsigned int ebCount, std::vector<unsigned int> vbCounts, std::vector<VBOInfo> vboInfos);

		private:
			unsigned int m_VAO, m_EBO;
			std::vector<unsigned int> m_VBOs;
	};
}

#endif