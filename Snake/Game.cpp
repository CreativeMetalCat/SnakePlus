#include "Game.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <nlohmann/json.hpp>

#include <World/Wall.h>
#include <GameplayObjects/Apple.h>
#include <GameplayObjects/EndFlag.h>


Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			throw std::exception(IMG_GetError());
		}
		if (TTF_Init() == -1)
		{
			throw std::exception(TTF_GetError());
		}
		window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_size.x, window_size.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (!window)
		{
			throw std::exception(SDL_GetError());
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (!renderer)
			{
				throw std::exception(SDL_GetError());
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, defaultClearColor.r, defaultClearColor.b, defaultClearColor.g, 255);
			}
		}
	}
	else
	{
		throw std::exception(SDL_GetError());
	}
}

SDL_Texture* Game::GetTexture(std::string name)
{
	auto it = std::find_if(textures.begin(), textures.end(), [name](AtlasTexture t) {return t.name == name; });
	return it == textures.end() ? nullptr : (*it).texture;
}

SDL_Texture* Game::LoadTextureFromFile(std::string filename)
{
	if (SDL_Surface* surface = IMG_Load(filename.c_str()))
	{
		return SDL_CreateTextureFromSurface(renderer, surface);
	}
	return nullptr;
}

void Game::EndLevel()
{
	needsToClose = true;
}

bool Game::LoadLevel(std::string levelFilePath)
{
	std::ifstream assetStream(levelFilePath, std::ios::in);
	std::string levelText;
	if (assetStream.is_open())
	{
		std::stringstream sstr;
		sstr << assetStream.rdbuf();
		levelText = sstr.str();
		assetStream.close();

		nlohmann::json items = nlohmann::json::parse(levelText);
		//spawn elements for background aka layer0
		int fieldSize = atoi(items["size"].get<std::string>().c_str());

		player = new Player(this);
		player->SnakeHead = SpawnWorldObject<Snake>("snek", (int)RenderLayers::Snake, Snake::Type::Head,
			glm::vec2
			(
				items["playerSpawn"]["location"]["x"].get<int>() * GridSize,
				items["playerSpawn"]["location"]["y"].get<int>() * GridSize
			));
		player->SnakeTail = SpawnWorldObject<Snake>("snekEnd", (int)RenderLayers::Snake, Snake::Type::Tail, glm::vec2(0, 0));

		for (int x = 0; x < fieldSize; x++)
		{
			for (int y = 0; y < fieldSize; y++)
			{
				SpawnWorldObject<WorldObject>
					(
						"backgroundTile" + std::to_string(x * y), 
						(int)RenderLayers::Background, 
						glm::vec4(0 + rand() % ((3 + 1)), 128, 16, 16), 
						glm::vec2(x * GridSize, y * GridSize)
					);
			}
		}

		for (nlohmann::json::iterator it = items["walls"].begin(); it != items["walls"].end(); it++)
		{
			SpawnWorldObject<Wall>
				(
					"wall",
					(int)RenderLayers::Wall,
					glm::vec2
					(
						(*it)["location"]["x"].get<int>(),
						(*it)["location"]["y"].get<int>()
					)* (float)GridSize
				);
		}

		for (nlohmann::json::iterator it = items["apples"].begin(); it != items["apples"].end(); it++)
		{
			SpawnWorldObject<Apple>
				(
					"apple",
					(int)RenderLayers::GameplayObjects,
					glm::vec2
					(
						(*it)["location"]["x"].get<int>(),
						(*it)["location"]["y"].get<int>()
					) * (float)GridSize
				);
		}
		totalAppleCount = items["apples"].size();

		SpawnWorldObject<EndFlag>("endFlag",(int)RenderLayers::GameplayObjects, glm::vec2
		(
			items["finish"]["location"]["x"].get<int>() * GridSize,
			items["finish"]["location"]["y"].get<int>() * GridSize
		));
	}
	else
	{
		return false;
	}
}

void Game::ClearLevel()
{
	for (int i = 0; i < objects.size(); i++)
	{
		RenderLayersObjects[objects[i]->GetRenderLayerId()].erase
		(
			std::find(RenderLayersObjects[objects[i]->GetRenderLayerId()].begin(),
				RenderLayersObjects[objects[i]->GetRenderLayerId()].end(),
				objects[i])
		);
		objects[i]->Destroy();
		objects[i] = nullptr;
	}
	player = nullptr;
}

void Game::Init()
{
	textures.push_back(AtlasTexture("atlas", LoadTextureFromFile("atlas.png")));
	textures.push_back(AtlasTexture("ui_atlas", LoadTextureFromFile("atlas_ui.png")));

	CurrentCamera = new Camera(this);

	LoadLevel("levels/level_face.json");
}

void Game::Close()
{
	for (int i = 0; i < objects.size(); i++)
	{
		RenderLayersObjects[objects[i]->GetRenderLayerId()].erase
		(
			std::find(RenderLayersObjects[objects[i]->GetRenderLayerId()].begin(),
			RenderLayersObjects[objects[i]->GetRenderLayerId()].end(),
			objects[i])
		);

		objects[i]->Destroy();
		objects[i] = nullptr;
	}
	delete test;

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	//TTF_CloseFont(baseFont);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::Draw()
{
	SDL_RenderClear(renderer);
	for (int i = 0; i < (int)RenderLayers::MAX; i++)
	{
		for (int id = 0; id < RenderLayersObjects[i].size(); id++)
		{
			if (RenderLayersObjects[i][id]->Visible)
			{
				RenderLayersObjects[i][id]->Draw();
			}
		}
	}
	SDL_RenderPresent(renderer);
}

void Game::Update()
{
	deltaTime = (float)((SDL_GetPerformanceCounter() - lastTime) * 1000 / (double)SDL_GetPerformanceFrequency());
	if (deltaTime < 1)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			InputEvent* inputEvent = new InputEvent();
			inputEvent->Type = (InputType)event.type;
			inputEvent->Code = event.key.keysym.sym;

			if (event.type == SDL_QUIT)
			{
				needsToClose = true;
			}
			if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					window_size_old = window_size;
					window_size = { event.window.data1,event.window.data2 };

					for (int i = 0; i < objects.size(); i++)
					{
						objects[i]->GetTexture()->OnWindowResize();
					}
					test->OnWindowResize();
				}
			}
			player->UpdateInput(inputEvent);
		}
	}
	lastTime = SDL_GetPerformanceCounter();
	for (int i = objects.size() - 1; i >= 0; i--)
	{
		if (!objects[i]->Valid())
		{
			RenderLayersObjects[objects[i]->GetRenderLayerId()].erase
			(
				std::find(RenderLayersObjects[objects[i]->GetRenderLayerId()].begin(),
				RenderLayersObjects[objects[i]->GetRenderLayerId()].end(),
				objects[i])
			);

			objects[i]->Destroy();
			objects[i] = nullptr;
			objects.erase(objects.begin() + i);
		}
	}
}

AtlasTexture::AtlasTexture(std::string _name, SDL_Texture* _texture)
	:name(_name),texture(_texture)
{
}
