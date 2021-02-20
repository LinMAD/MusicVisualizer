#include <iostream>
#include <algorithm>
#include "Logger.h"
#include "Graphic/Renderer.h"
#include "Audio/Player.h"

using namespace MV;

// TODO Move files to other place to make main.cpp clean.

char* GetCmdOption(char** begin, char** end, const std::string& option)
{
	char** itr = std::find(begin, end, option);
	if (itr != end && ++itr != end) return *itr;
	return 0;
}

int main(int argc, char* argv[])
{
	char* filename = GetCmdOption(argv, argv + argc, "-f");
	if (filename == nullptr)
	{
		LOGGER_DEBUG("Provide audio file path with input CMD option '-f'");
		return 1;
	}

	auto player = new Player();
	auto renderer = Renderer::GetActuallRenderer();

	player->Add(filename);

	while (renderer->IsRunning())
	{
		renderer->HandleEvents();
		player->Play(filename);

		renderer->Draw(player->GetAudioData(filename));
	}

	return 0;
}