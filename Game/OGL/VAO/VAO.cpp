#include "VAO.h"

namespace OGL
{
	VAO::VAO(unsigned int ebCount, std::vector<unsigned int> vbCounts, std::vector<VBOInfo> vboInfos)
	{
		initialize(ebCount, vbCounts, vboInfos);
	}
	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_EBO);
		for (unsigned int vb : m_VBOs)
		{
			glDeleteBuffers(1, &vb);
		}
	}

	void VAO::bind() const
	{
		glBindVertexArray(m_VAO);
	}

	void VAO::updateVB(unsigned int off, std::vector<float> buffer, unsigned int bindingIdx) const
	{
		glNamedBufferSubData(m_VBOs[bindingIdx], off * sizeof(float), buffer.size() * sizeof(float), buffer.data());
	}
	void VAO::updateEB(unsigned int off, std::vector<unsigned int> buffer) const
	{
		glNamedBufferSubData(m_EBO, off * sizeof(unsigned int), buffer.size() * sizeof(unsigned int), buffer.data());
	}

	void VAO::recreateVB(unsigned int vbCount, unsigned int usage, unsigned int bindingIdx) const
	{
		glNamedBufferData(m_VBOs[bindingIdx], vbCount * sizeof(float), nullptr, usage);
	}
	void VAO::recreateEB(unsigned int ebCount, unsigned int usage) const
	{
		glNamedBufferData(m_EBO, ebCount * sizeof(unsigned int), nullptr, usage);
	}

	void VAO::initialize(unsigned int ebCount, std::vector<unsigned int> vbCounts, std::vector<VBOInfo> vboInfos)
	{
		glCreateVertexArrays(1, &m_VAO);

		glCreateBuffers(1, &m_EBO);
		glNamedBufferData(m_EBO, ebCount * sizeof(unsigned int), nullptr, GL_STATIC_DRAW);
		glVertexArrayElementBuffer(m_VAO, m_EBO);

		for (unsigned int i = 0; i < vbCounts.size(); i++)
		{
			unsigned int buffer;
			glCreateBuffers(1, &buffer);
			glNamedBufferData(buffer, vbCounts[i] * sizeof(float), nullptr, GL_STATIC_DRAW);
			glVertexArrayVertexBuffer(m_VAO, vboInfos[i].bindingIdx, buffer, 0, vboInfos[i].stride);

			for (const AttribInfo& info : vboInfos[i].attribs)
			{
				glVertexArrayAttribFormat(m_VAO, info.attribIdx, info.count, GL_FLOAT, GL_FALSE, info.offset);
				glVertexArrayAttribBinding(m_VAO, info.attribIdx, vboInfos[i].bindingIdx);
				glEnableVertexArrayAttrib(m_VAO, info.attribIdx);
			}
			m_VBOs.push_back(buffer);
		}
	}
}