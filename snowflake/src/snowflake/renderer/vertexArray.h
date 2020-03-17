#pragma once
#include "buffer.h"

namespace SF {

	class VertexArray
	{

	public:
		VertexArray() {}
		~VertexArray() {}

		static VertexArray* create();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void setIndexBuffer(IndexBuffer* indexBuffer) = 0;

	};

}