#include "Mesh.h"

#include <GL/glew.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

//std::vector<Mesh::Ptr> Mesh::loadMeshesFromFile(const std::string& path) {
//
//
//	std::vector<Mesh::Ptr> mesh_ptrs;
//
//	auto scene = aiImportFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
//	for (size_t m = 0; m < scene->mNumMeshes; ++m) {
//		auto mesh = scene->mMeshes[m];
//		auto faces = mesh->mFaces;
//		auto verts = mesh->mVertices;
//		auto texCoords = mesh->mTextureCoords[0];
//
//		vector<double> vertex_data;
//
//
//		for (size_t i = 0; i < mesh->mNumVertices; ++i) {
//			vertex_data.push_back(verts[i].x);
//			vertex_data.push_back(verts[i].y);
//			vertex_data.push_back(verts[i].z);
//			vertex_data.push_back(texCoords[i].x);
//			vertex_data.push_back(texCoords[i].y);
//		}
//
//		vector<unsigned int> index_data;
//		for (size_t f = 0; f < mesh->mNumFaces; ++f) {
//			index_data.push_back(faces[f].mIndices[0]);
//			index_data.push_back(faces[f].mIndices[1]);
//			index_data.push_back(faces[f].mIndices[2]);
//		}
//
//		auto mesh_ptr = make_shared<Mesh>(Mesh::Formats::F_V3T2, vertex_data.data(), mesh->mNumVertices, index_data.data(), index_data.size());
//		mesh_ptrs.push_back(mesh_ptr);
//
//	}
//
//	return mesh_ptrs;
//}

Mesh::Mesh(Formats format, const void* vertex_data, unsigned int numVerts, const unsigned int* index_data, unsigned int numIndexs) :
	_format(format), _numVerts(numVerts), _numIndexs(numIndexs)
{

	glGenBuffers(1, &_vertex_buffer_id);
	glBindBuffer(GL_VERTEX_ARRAY, _vertex_buffer_id);
	switch (_format)
	{
	case Mesh::Formats::F_V3T2:
		glBufferData(GL_VERTEX_ARRAY, sizeof(double) * 5 * _numVerts, vertex_data, GL_STATIC_DRAW);
		break;
	default:
		throw "not implmented";
		break;
	}

	glBindBuffer(GL_VERTEX_ARRAY, 0);
	glGenBuffers(1, &_index_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndexs, index_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::draw() {

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	switch (_format)
	{
	case Mesh::Formats::F_V3T2:
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_DOUBLE, sizeof(double) * 5, nullptr);
		glTexCoordPointer(2, GL_DOUBLE, sizeof(double) * 5, (void*)(sizeof(double) * 3));
		break;
	default:
		throw "not implemented";
		break;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
	glDrawElements(GL_TRIANGLES, _numIndexs, GL_UNSIGNED_INT, nullptr);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
}
