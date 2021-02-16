#include <iostream>
#include "Logger.h"
#include "Graphic/Renderer.h"

using namespace MV;

int main(int argc, char* argv[])
{
	// TODO Move to application manager
	auto renderer = Renderer::GetActuallRenderer();

	while (true)
	{
		renderer->Clear();
		renderer->Draw();
	}

	return 0;
}