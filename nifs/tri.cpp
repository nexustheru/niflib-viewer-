#include <tri.h>

void trifile::readintofile(const char* filename)
{
	try
	{
trifile ttrifile;
   FILE* fp ;
	fp= fopen(filename, "rb");
	size_t count;
   count = fread(&ttrifile, 1, sizeof(trifile), fp);
	}
	catch(exception ex)
	{
		printf("%%",ex.what());
	}
	catch(...)
	{
		printf("%%","error");
	}
   
   
}