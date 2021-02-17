#include <iostream>
#include "Logger.h"
#include "Graphic/Renderer.h"
#include "Audio/Player.h"

using namespace MV;

int main(int argc, char* argv[])
{
	// TODO Move to application manager ?
	auto renderer = Renderer::GetActuallRenderer();
	auto player = new Player();

	while (renderer->IsRunning())
	{
		renderer->Update();
		renderer->Draw();

		player->Play("test.wav");
	}

	return 0;
}