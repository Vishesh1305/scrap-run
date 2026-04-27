#include "Renderer/Renderer.h"
#include "Game/Game.h"
#include "raylib.h"

int main()
{
	Renderer renderer;
	Game game;
	while (!renderer.ShouldClose())
	{
		game.Update(GetFrameTime());
		game.HandleInput();
		renderer.Draw(game);
	}
	return 0;
}
