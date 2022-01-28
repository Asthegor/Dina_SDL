#pragma once
#include <locale>

extern Dina::DinaGame* Dina::CreateGame();

int main(int argc, char* argv[])
{
	std::locale::global(std::locale{ "" });

	Dina::Log::Init();
	DINA_CORE_INFO("SpdLog initialized successfully.");

	auto game = Dina::CreateGame();
	DINA_CORE_INFO("Dina Game Engine initialized successfully.");

	game->Run();
	delete game;

	return 0;
}
