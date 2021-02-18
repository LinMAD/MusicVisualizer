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
	player->Add("test.wav");

	while (renderer->IsRunning())
	{
		renderer->HandleEvents();

		player->Play("test.wav");

		renderer->Draw(player->GetAudioData("test.wav"));
	}

	return 0;
}