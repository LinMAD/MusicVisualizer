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
	if (itr != end && ++itr != end)
	    return *itr;

	return nullptr;
}

int main(int argc, char* argv[])
{
	char* inputFilePath = GetCmdOption(argv, argv + argc, "-f");
	if (inputFilePath == nullptr)
	{
		LOG("Provide audio file path with input CMD option '-f'");
		return 1;
	}

	std::string filename(inputFilePath);
	if(filename.substr(filename.find_last_of('.') + 1) != "wav")
	{
		LOG("Given not 'wav' file");
		return 1;
	}

	auto* player = new Player();
	player->Add(filename);

	while (MV::Renderer::IsRunning())
	{
		MV::Renderer::HandleEvents();
		player->Play(filename);

		MV::Renderer::Draw(*player->GetAudioData(filename));
	}

	delete(player);
	delete(inputFilePath);

	return 0;
}