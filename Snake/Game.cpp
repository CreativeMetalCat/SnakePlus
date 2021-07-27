#include "Game.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

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

void Game::Init()
{
	textures.push_back(AtlasTexture("atlas", LoadTextureFromFile("atlas.png")));
	test = Texture::LoadFromAtlas(this, { 0,64,16,16 });
	test->SetLocation(glm::vec2(50, 123));

	player = new Player(this);
	player->SnakeHead = SpawnWorldObject<Snake>("snek", 0, Snake::Type::Head, glm::vec2(GridSize, 0));
	player->SnakeHead = SpawnWorldObject<Snake>("snekEnd", 0, Snake::Type::Tail, glm::vec2(0, 0));
}

void Game::Close()
{
	for (int i = 0; i < objects.size(); i++)
	{
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
	for (int i = 0; i < 3; i++)
	{
		for (int id = 0; id < RenderLayersObjects[i].size(); id++)
		{
			RenderLayersObjects[i][id]->Draw();
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
