#include <GL/glew.h>
#include "snowflake/renderer/vertexArray.h"

namespace SF {

	class OpenGLVertexArray : public VertexArray
	{

	private:
		uint32_t m_ID;
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer;


	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

	};
}