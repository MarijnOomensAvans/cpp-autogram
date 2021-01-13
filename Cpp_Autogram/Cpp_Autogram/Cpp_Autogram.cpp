#define _CRTDBG_MAP_ALLOC
#include "AutogramGenerator.h"
int main(int arc, char* argv)
{
	try
	{
		AutogramGenerator generator;
	}
	catch (const std::exception& ex)
	{
		std::cerr << argv[0] << ": " << ex.what() << '\n';
	}
	catch (...) {
		std::cerr << argv[0] << ": unknown error" << '\n';
	}
    _CrtDumpMemoryLeaks();

    return 0;
}