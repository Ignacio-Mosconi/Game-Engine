#include "Cube.h"
#include "Material.h"
#include "Renderer.h"

namespace gn
{
	Cube::Cube(Renderer* renderer, Material* material) : Mesh(renderer, material, 8)
	{
		std::cout << "Cube::Cube()" << std::endl;
	}

	Cube::~Cube()
	{
		std::cout << "Cube::~Cube()" << std::endl;
	}

	void Cube::draw() const
	{
		Mesh::draw();

		_renderer->enableAttribute(0);
		_renderer->enableAttribute(1);
		_renderer->bindBuffer(0, 3, _vertexBufferID);
		_renderer->bindBuffer(1, 3, _colorBufferID);
		_renderer->bindIndexBuffer(_indexBufferID);
		_renderer->drawIndexedBuffer(PrimitiveType::TRIANGLE, _indexBufferData->size());
		_renderer->disableAttribute(0);
		_renderer->disableAttribute(1);
	}

	float* Cube::setVertices(unsigned int vertexComponents, float width, float height, float depth) const
	{
		float valueX = width * 0.5f;
		float valueY = height * 0.5f;
		float valueZ = depth * 0.5f;

		float* vertexBufferData = new float[_vertexCount * vertexComponents]
		{
			-valueX ,-valueY, -valueZ,
			-valueX, valueY, -valueZ,
			valueX, valueY, -valueZ,
			valueX, -valueY, -valueZ,

			valueX, -valueY, valueZ,
			valueX, valueY, valueZ,
			-valueX, valueY, valueZ,
			-valueX, -valueY, valueZ,
		};

		return vertexBufferData;
	}

	std::vector<unsigned short>* Cube::setVerticesIndexes() const
	{
		std::vector<unsigned short>* indexBufferData = new std::vector<unsigned short>
		{
			0, 1, 2,
			0, 2, 3,
			2, 3, 4,
			4, 2, 5,
			4, 5, 6,
			4, 6, 7
		};

		return indexBufferData;
	}

	void Cube::setFaceColors(float front[3], float back[3], float left[3], float right[3], float bottom[3], float top[3])
	{
		/*float* colorBufferData = new float[_vertexCount * 3]
		{
			right[0], right[1], right[2],
			right[0], right[1], right[2],
			right[0], right[1], right[2],
			
			back[0], back[1], back[2],
			back[0], back[1], back[2],
			back[0], back[1], back[2],
			
			bottom[0], bottom[1], bottom[2],
			bottom[0], bottom[1], bottom[2],
			bottom[0], bottom[1], bottom[2],

			back[0], back[1], back[2],
			back[0], back[1], back[2],
			back[0], back[1], back[2],
			
			right[0], right[1], right[2],
			right[0], right[1], right[2],
			right[0], right[1], right[2],

			bottom[0], bottom[1], bottom[2],
			bottom[0], bottom[1], bottom[2],
			bottom[0], bottom[1], bottom[2],

			front[0], front[1], front[2],
			front[0], front[1], front[2],
			front[0], front[1], front[2],			
			
			left[0], left[1], left[2],
			left[0], left[1], left[2],
			left[0], left[1], left[2],

			left[0], left[1], left[2],
			left[0], left[1], left[2],
			left[0], left[1], left[2],

			top[0], top[1], top[2],
			top[0], top[1], top[2],
			top[0], top[1], top[2],

			top[0], top[1], top[2],
			top[0], top[1], top[2],
			top[0], top[1], top[2],

			front[0], front[1], front[2],
			front[0], front[1], front[2],
			front[0], front[1], front[2]
		};
		
		_colorBufferData = setVerticesColor(colorBufferData, 3);

		if (_colorBufferID == -1)
		{
			int bufferSize = sizeof(float) * _vertexCount * 3;
			_colorBufferID = _renderer->generateVertexBuffer(_colorBufferData, bufferSize);
		}

		delete colorBufferData;*/
	}
}