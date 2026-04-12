#include <raylib.h>
#include "gameMain.h"
#include <asserts.h>

struct GameData
{
	float positionX = 500;
	float positionY = 500;
}gameData;

bool initGame()
{
	return true;
}

bool updateGame()
{
	float deltaTime = GetFrameTime();
	if (deltaTime > 1.f / 5) { deltaTime = 1 / 5.f; }

	if (IsKeyDown(KEY_A)) { gameData.positionX -= 500 * deltaTime; }
	if (IsKeyDown(KEY_D)) { gameData.positionX += 500 * deltaTime; }
	if (IsKeyDown(KEY_W)) { gameData.positionY -= 500 * deltaTime; }
	if (IsKeyDown(KEY_S)) { gameData.positionY += 500 * deltaTime; }

	DrawRectangle(gameData.positionX, gameData.positionY, 50, 50, YELLOW);

	return true;
}

void closeGame()
{
	
}