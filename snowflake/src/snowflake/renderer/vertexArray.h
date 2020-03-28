#pragma once
#include "buffer.h"

namespace SF {

	class VertexArray
	{

	protected:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;

	public:
		VertexArray() = default;
		~VertexArray() {}

		static Ref<VertexArray> create();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(Ref<VertexBuffer> vertexBuffer) {
		
			this->bind();
			vertexBuffer->bind();

			uint32_t index = 0;
			const auto& layout = vertexBuffer->getLayout();
			for (const auto element : layout) {

				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, element.getComponentSize(), bufferElementTypeToGLenum(element.m_Type), element.m_Normalized, layout.getStride(), (void*)(element.m_Offset));
				index++;
			}

			this->m_VertexBuffers.push_back(vertexBuffer);

		}

		virtual void setIndexBuffer(Ref<IndexBuffer> indexBuffer) {
		
			this->m_IndexBuffer = indexBuffer;

			this->bind();
			indexBuffer->bind();
		
		}

		Ref<IndexBuffer> getIndexBuffer() const { return this->m_IndexBuffer; };

	};

}