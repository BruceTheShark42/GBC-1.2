#pragma once

namespace gbc
{
	enum class ShaderDataType
	{
		None,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static unsigned int shaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:  return 4 * 1;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Mat3:   return 4 * 3 * 3;
			case ShaderDataType::Mat4:   return 4 * 4 * 4;
			case ShaderDataType::Int:    return 4 * 1;
			case ShaderDataType::Int2:   return 4 * 2;
			case ShaderDataType::Int3:   return 4 * 3;
			case ShaderDataType::Int4:   return 4 * 4;
			case ShaderDataType::Bool:   return 1;
		}

		GBC_CORE_ASSERT(false, "Unknown shader data type!");
		return 0;
	}

	struct BufferElement
	{
		ShaderDataType type;
		std::string name;
		unsigned int size, offset;
		bool normalized;

		BufferElement(ShaderDataType type, const std::string &name, bool normalized = false)
			: type(type), name(name), size(shaderDataTypeSize(type)), offset(0), normalized(normalized) {}

		unsigned int getComponentCount() const
		{
			switch (type)
			{
				case ShaderDataType::Float:  return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;
				case ShaderDataType::Mat3:   return 3 * 3;
				case ShaderDataType::Mat4:   return 4 * 4;
				case ShaderDataType::Int:    return 1;
				case ShaderDataType::Int2:   return 2;
				case ShaderDataType::Int3:   return 3;
				case ShaderDataType::Int4:   return 4;
				case ShaderDataType::Bool:   return 1;
			}

			GBC_CORE_ASSERT(false, "Unknown shader data type!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: elements(elements), stride(0)
		{
			for (auto &element : this->elements)
			{
				element.offset = stride;
				stride += element.size;
			}
		}

		inline const std::vector<BufferElement>& getElements() const { return elements; }
		inline unsigned int getStride() const { return stride; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.end(); }
	private:
		std::vector<BufferElement> elements;
		unsigned int stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout &layout) = 0;

		virtual void setData(const void *data, unsigned int size) = 0;
		
		static Ref<VertexBuffer> create(float *vertices, unsigned int size);
		static Ref<VertexBuffer> create(unsigned int size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual unsigned int getCount() const = 0;

		static Ref<IndexBuffer> create(unsigned int* indices, unsigned int size);
	};
}
