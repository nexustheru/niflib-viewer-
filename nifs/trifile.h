#include <iostream>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <tri.h>


class Trifile
{
public:
    header Header;
	std::vector<fCOORDS> vertices;
	std::vector<fCOORDS> modvertices;
	std::vector<triCOORDS> trifaces;	
	std::vector<quadCOORDS> quadfaces;	
	std::vector<uvCOORDS> uvvertices;  
	std::vector<triCOORDS> uvtrifaces;	
	std::vector<quadCOORDS> uvquadfaces;

private:

};

for(int i=0 ;i < Trifile.