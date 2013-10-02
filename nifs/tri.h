#include <iostream>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <vector>

typedef uint8_t ubyte;
namespace trifile
{

struct header
{
char indentifier[2];	// Always FR
char filetype[3];	// Always TRI
char version[3];
int vertices;	// number of vertices
int polytris;	// number of tri faces
int polyquads;	// number of quad faces
int unknown2;
int unknown3;
int uvvertices;	// number of uv map vertices
int flags;	// flags?
				// bit 0 must be 1 or crashes
				// bit 1 true=don't display face
				// bit 2 no effect?
int nummorphs;	// number of morphs
int nummodifiers;	// number of modifiers
int modvertices;	// number of vertices to replace by modifiers
int unknown7;
int unknown8;
int unknown9;
int unknown10;
};


struct fCOORDS 
{
	float x,y,z;
};

struct triCOORDS 
{
	int a,b,c;
};

struct quadCOORDS 
{
	int a,b,c,d;
};


struct uvCOORDS 
{
	float u,v;
};

struct morphvertices 
{
	short x,y,z;
};

struct morph
{
	int size;
	string name;
	int scale;
};

};