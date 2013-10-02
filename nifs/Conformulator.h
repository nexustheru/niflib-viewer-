#include <vector>
#include <iostream>
#include <string>
using namespace std;
struct Vertex{
	float x,y,z;
};

struct VertexShort{
	short x,y,z;
};

struct UVdata{
	float u,v;
};

struct TriData{
	int a,b,c;
};

struct neareststruct{
	float distsq;
	int vertexnum;
};

struct TriMorphDataType{
	std::string MorphName;
	int scalex,scaley,scalez,scale;
	std::vector<VertexShort> MorphData;
};