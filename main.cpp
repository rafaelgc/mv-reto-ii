#include "App.hpp"

#ifdef _WIN32
int WinMain()
{
	int argc = 0; char *argv = "";
	App app(argc, &argv);
	app.run();

	return 0;
}
#else
int main(int argc, char** argv)
{
	App app(argc, &argv);
	app.run();

	return 0;
}
#endif
