#pragma once
#include <GL/glew.h>
#include <snowflake/logging/log.h>
#include <snowflake/core/core.h>

namespace SF {

	enum class BufferElementType {

		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int1, Int2, Int3, Int4,
		Bool

	};

	static uint32_t getBufferElementTypeSize(BufferElementType type) {

		switch (type)
		{
		case SF::BufferElementType::None:	break;
		case SF::BufferElementType::Float:	return sizeof(float);
		case SF::BufferElementType::Float2:	return sizeof(float) * 2;
		case SF::BufferElementType::Float3:	return sizeof(float) * 3;
		case SF::BufferElementType::Float4:	return sizeof(float) * 4;
		case SF::BufferElementType::Mat3:	return sizeof(float) * 3 * 3;
		case SF::BufferElementType::Mat4:	return sizeof(float) * 4 * 4;
		case SF::BufferElementType::Int1:	return sizeof(int);
		case SF::BufferElementType::Int2:	return sizeof(int) * 2;
		case SF::BufferElementType::Int3:	return sizeof(int) * 3;
		case SF::BufferElementType::Int4:	return sizeof(int) * 4;
		case SF::BufferElementType::Bool:	return sizeof(bool);
		default: break;
		}

		SF_CORE_ERROR("unkonwn element-type!");
		return 0;

	}

	static GLenum bufferElementTypeToGLenum(BufferElementType type) {

		switch (type)
		{
		case SF::BufferElementType::None:	break;
		case SF::BufferElementType::Float:	
		case SF::BufferElementType::Float2:	
		case SF::BufferElementType::Float3:	
		case SF::BufferElementType::Float4:	
		case SF::BufferElementType::Mat3:	
		case SF::BufferElementType::Mat4:	return GL_FLOAT;
		case SF::BufferElementType::Int1:	
		case SF::BufferElementType::Int2:	
		case SF::BufferElementType::Int3:	
		case SF::BufferElementType::Int4:	return GL_INT;
		case SF::BufferElementType::Bool:	return GL_BOOL;
		default: break;
		}

		SF_CORE_ERROR("unkonwn element-type!");
		return 0;

	}

	/********* Buffer	*******************************************/
	class Buffer {

	public:
		Buffer() = default;
		
		virtual ~Buffer();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;


	};

	/********* BufferElement	**************************************/
	struct BufferElement {
		
		std::string m_ElementName;
		BufferElementType m_Type;
		uint32_t m_Size;
		size_t m_Offset;
		bool m_Normalized;
		
		BufferElement() = default;
		BufferElement(BufferElementType type, const std::string& name, const bool& normalized = false);

		virtual ~BufferElement() {}

		uint32_t getComponentSize() const {

			switch (this->m_Type)
			{
			case SF::BufferElementType::None:	break;
			case SF::BufferElementType::Float:	return 1;
			case SF::BufferElementType::Float2:	return 2;
			case SF::BufferElementType::Float3:	return 3;
			case SF::BufferElementType::Float4:	return 4;
			case SF::BufferElementType::Mat3:	return 3 * 3;
			case SF::BufferElementType::Mat4:	return 4 * 4;
			case SF::BufferElementType::Int1:	return 1;
			case SF::BufferElementType::Int2:	return 2;
			case SF::BufferElementType::Int3:	return 3;
			case SF::BufferElementType::Int4:	return 4;
			case SF::BufferElementType::Bool:	return 1;
			default:
				break;
			}

			return 0;

		}

	};



	/********* BufferLayout	**************************************/
	class BufferLayout {

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;

	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
			
			size_t offset = 0;
			this->m_Stride = 0;

			for (auto& element : this->m_Elements) {

				element.m_Offset = offset;
				offset += element.m_Size;
				this->m_Stride += element.m_Size;

			}
		
		}

		~BufferLayout() {};

		const std::vector<BufferElement>& getElements() const { return this->m_Elements; }
		const uint32_t& getStride() const { return this->m_Stride; };

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	};


	class VertexBuffer : public Buffer {

	protected:
		uint32_t m_Size = 0;

	public:
		VertexBuffer() {}
		virtual ~VertexBuffer() {}

		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static Ref<VertexBuffer> create(float* data, uint32_t size);

		const uint32_t& getSize() const { return this->m_Size; }

		virtual float* map() const = 0;
		virtual void unmap() const = 0;

	};

	class IndexBuffer : public Buffer {

	protected:
		uint32_t m_Size;

	public:
		IndexBuffer() {}
		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static Ref<IndexBuffer> create(uint32_t* data, uint32_t size);

		const uint32_t& getSize() const { return this->m_Size; }

		virtual uint32_t* map() const = 0;
		virtual void unmap() const = 0;

	};

}