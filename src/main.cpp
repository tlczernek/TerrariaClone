#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1920, 1080, "Window test");

	rlImGuiSetup(true);

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.FontGlobalScale = 2;

	while (!WindowShouldClose())
		{
		BeginDrawing();
		ClearBackground(BLACK);


		//docking
		rlImGuiBegin();
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);


		
		DrawRectangle(650, 650, 100, 100, PINK);
		DrawRectangle(700, 700, 100, 100, { 255, 0, 0, 150 });
		

		DrawText("Holy shit it's open", 600, 200, 40, RED);

		ImGui::Begin("test");
		
		if (ImGui::Button("button")) {
			std::cout << "Button pressed\n";
		}

		ImGui::End();


		ImGui::Begin("second window");
		ImGui::Text("window2");
		ImGui::NewLine();
		static float a = 0;
		ImGui::SliderFloat("slider", &a, 0, 1);
		ImGui::End();




		rlImGuiEnd();
		
		EndDrawing();
		}

	rlImGuiShutdown();
	
	CloseWindow();

	return 0;
}