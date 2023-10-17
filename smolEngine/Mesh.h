#pragma once
#include <vector>
#include <memory>

#include "Graphic.h"
#include "Texture2D.h"
class Mesh :
    public Graphic
{
public:
    enum class Formats { F_V3, F_V3T2, F_V3C4, F_V3C4T2 };

private:
    Formats _format;

    unsigned int _vertex_buffer_id;
    unsigned int _numVerts;

    unsigned int _index_buffer_id;
    unsigned int _numIndexs;

public:
    //things missing here
   /* typedef shared_ptr<Mesh> Ptr;
    Texture2D::Ptr texture_ptr;*/

    Mesh(Formats format, const void* vertex_data, unsigned int numVerts, const unsigned int* index_data, unsigned int numIndexs);
    void draw();

    /* static std::vector<Ptr> loadMeshesFromFile(const std::string& path);*/

private:
    Mesh(const Mesh&);
    Mesh& operator=(const Mesh&);

};
