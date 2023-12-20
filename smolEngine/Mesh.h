#pragma once

#include <vector>
#include <memory>
#include <string>

#include "types.h"
#include "glmath.h"
#include "Graphic.h"
#include "Texture2D.h"
#include "Triangle.h"
#include "BoundingBox.h"


class Mesh;

struct PTRMeshData
{
	std::vector<std::shared_ptr<Mesh>> mesh_ptrs;
	std::vector<Triangle> triangles;
	std::vector<mat4> transforms;
};

class Mesh : public Graphic
{
public:
	enum Formats { F_V3, F_V3C4, F_V3T2 };
	struct V3 { vec3f v; };
	struct V3C4 { vec3f v; vec4f c; };
	struct V3T2 { vec3 v; vec2 t; };

private:
	const enum Formats _format;

	unsigned int _vertex_buffer_id = 0;
	const unsigned int _numVerts;

	unsigned int _indexs_buffer_id = 0;
	const unsigned int _numIndexs;
 
public:

	
	unsigned int mMaterialIndex;
	typedef std::shared_ptr<Mesh> Ptr;
	

	static PTRMeshData loadFromFile(const std::string& path);

	Texture2D::Ptr texture;

	Mesh(Formats format, const void* vertex_data, unsigned int numVerts, const unsigned int* indexs_data = nullptr, unsigned int numIndexs = 0);
	Mesh(Mesh&& b) noexcept;
	void draw();
	~Mesh();


	static std::vector<BoundingBox> CreateMeshSegments(size_t maxTrianglesPerSegment, std::vector<Triangle> triangles);
	std::vector<Triangle> GetTriangles(const std::vector<V3T2>& vertexData, const std::vector<unsigned int>& indexData) const;

private:
	std::vector<BoundingBox> MeshSegments;
	Mesh(const Mesh& cpy);
	Mesh& operator=(const Mesh&);
};



