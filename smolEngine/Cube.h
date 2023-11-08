#pragma once

#include "types.h"
#include "Graphic.h"

struct Cube : Graphic
{
	static const int NUM_FACES = 6;
	static const int NUM_TRIANGLES = NUM_FACES * 2;
	static const int NUM_VERTEXS = NUM_TRIANGLES * 3;

	const dvec3 a;
	const dvec3 b;
	const dvec3 c;
	const dvec3 d;
	const dvec3 e;
	const dvec3 f;
	const dvec3 g;
	const dvec3 h;

	const dvec3 red;
	const dvec3 green;
	const dvec3 blue;
	const dvec3 yellow;
	const dvec3 white;
	const dvec3 black;

	Cube();
};

