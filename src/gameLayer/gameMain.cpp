#include <raylib.h>
#include "gameMain.h"
#include <asserts.h>
#include <assetManager.h>
#include <gameMap.h>
#include <helpers.h>
#include <iostream>
#include <raymath.h>

struct GameData
{
	GameMap gameMap;
	Camera2D camera;

}gameData;

AssetManager assetManager;

bool initGame()
{
	assetManager.loadAll();

	gameData.gameMap.create(30, 10);

	gameData.gameMap.getBlockUnsafe(0, 0).type = Block::dirt;
	gameData.gameMap.getBlockUnsafe(1, 1).type = Block::grass;
	gameData.gameMap.getBlockUnsafe(2, 2).type = Block::goldBlock;
	gameData.gameMap.getBlockUnsafe(3, 3).type = Block::glass;
	gameData.gameMap.getBlockUnsafe(4, 4).type = Block::platform;

	gameData.camera.target = { 0,0 };
	gameData.camera.rotation = 0.0f;
	gameData.camera.zoom = 100.0f;
	
	return true;
}

int blockSelector = 0;

bool updateGame()
{
	float deltaTime = GetFrameTime();
	if (deltaTime > 1.f / 5) { deltaTime = 1 / 5.f; }

	gameData.camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }; //update position every frame

	ClearBackground({ 75, 75, 150, 255 });

#pragma region camera movement

	if (IsKeyDown(KEY_A)) gameData.camera.target.x -= 10.f * deltaTime;
	if (IsKeyDown(KEY_D)) gameData.camera.target.x += 10.f * deltaTime;
	if (IsKeyDown(KEY_W)) gameData.camera.target.y -= 10.f * deltaTime;
	if (IsKeyDown(KEY_S)) gameData.camera.target.y += 10.f * deltaTime;

#pragma endregion

	Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
	int blockX = (int)floor(worldPos.x);
	int blockY = (int)floor(worldPos.y);

	
	if (IsKeyPressed(KEY_KP_1)) blockSelector = 1;
	if (IsKeyPressed(KEY_KP_2)) blockSelector = 2;
	if (IsKeyPressed(KEY_KP_3)) blockSelector = 3;
	if (IsKeyPressed(KEY_KP_4)) blockSelector = 4;
	if (IsKeyPressed(KEY_KP_5)) blockSelector = 5;
	if (IsKeyPressed(KEY_KP_6)) blockSelector = 6;
	if (IsKeyPressed(KEY_KP_7)) blockSelector = 7;
	if (IsKeyPressed(KEY_KP_8)) blockSelector = 8;
	if (IsKeyPressed(KEY_KP_9)) blockSelector = 9;
	//std::cout << "Current value of blockSelector: " << blockSelector << "\n";


	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
		if (b)
		{
			*b = {};
		}
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
		if (b)
		{
			if (blockSelector == 1) {
				b->type = Block::gold;
			}
			else if (blockSelector == 2) {
				b->type = Block::glass;
			}
			else if (blockSelector == 3) {
				b->type = Block::dirt;
			}
			else if (blockSelector == 4) {
				b->type = Block::rubyBlock;
			}
			else if (blockSelector == 5) {
				b->type = Block::stone;
			}
			else if (blockSelector == 6) {
				b->type = Block::clay;
			}
			else if (blockSelector == 7) {
				b->type = Block::bricks;
			}
			else if (blockSelector == 8) {
				b->type = Block::ironBlock;
			}
			else if (blockSelector == 9) {
				b->type = Block::snowBricks;
			}
		}
		
	}

	BeginMode2D(gameData.camera);

	Vector2 topLeftView = GetScreenToWorld2D({ 0,0 }, gameData.camera);
	Vector2 bottomRightView = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, gameData.camera);

	int startXView = (int)floorf(topLeftView.x - 1);
	int endXView = (int)ceilf(bottomRightView.x + 1);
	int startYView = (int)floorf(topLeftView.y - 1);
	int endYView = (int)ceilf(bottomRightView.x + 1);

	startXView = Clamp(startXView, 0, gameData.gameMap.w - 1);
	endXView = Clamp(endXView, 0, gameData.gameMap.w - 1);

	startYView = Clamp(startYView, 0, gameData.gameMap.h - 1);
	endYView = Clamp(endYView, 0, gameData.gameMap.h - 1);

	for (int y= startYView; y<= endYView; y++)
		for (int x = startXView; x <= endXView; x++)
		{
			auto& b = gameData.gameMap.getBlockUnsafe(x, y);

			if (b.type != Block::air)
			{
				

				DrawTexturePro(
					assetManager.textures, 
					getTextureAtlas(b.type, 0, 32, 32), // source
					{ (float)x, (float)y, 1, 1}, //dest
					{0, 0}, // origin
					0, //rotation
					WHITE); //tint
			}
		}

	//draw selected block
	DrawTexturePro(
		assetManager.frame,
		{0, 0, (float)assetManager.frame.width, (float)assetManager.frame.height}, // source
		{ (float)blockX, (float)blockY, 1, 1 }, //dest
		{ 0, 0 }, // origin
		0.0f, //rotation
		WHITE); //tint


	EndMode2D();

	DrawFPS(10, 10);

	return true;
}

void closeGame()
{
	
}