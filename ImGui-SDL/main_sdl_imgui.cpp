// TODO: figure out why SDL.h include is needed on Android (it just a stuck without it)
#include <string>
#include "ImGui-SDL/include/app.h"

// Main code
int main(int argc, char** argv)
{
	app app(argc, argv);
	auto r = app.run();
	return r;
}
