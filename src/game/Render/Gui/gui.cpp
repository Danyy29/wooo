#include "gui.h"
#include "global.h"
#include "Utils.h"
#include "utils/gui-util.hpp"

void Gui::Render()
{
	auto& vars = Vars::GetInstance();
	
    ImGui::Begin("##Taiga74164", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    {
        ImGui::BeginGroup();
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
            GuiUtil::CenterText("Solo Leveling Cheeto", 0, 0);
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::PopStyleColor();
        }
        ImGui::EndGroup();

		GuiUtil::RainbowLine();
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		ImGui::BeginChild("##LeftSide", ImVec2(100, GuiUtil::GetY()), TRUE);
		ImGui::PopStyleColor();
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

#define MENU_MODULES(name, tab) ImGui::PushStyleColor(ImGuiCol_Button, m_MenuTab == (tab) ? active : inactive); \
		     ImGui::Button(name, ImVec2(90 - 10, 22)); \
		     if (ImGui::IsItemClicked()) m_MenuTab = tab; \
		     ImGui::PopStyleColor()

			MENU_MODULES("Features", 0);
			MENU_MODULES("Misc", 1);
			MENU_MODULES("About", 2);

#undef MENU_MODULES
		}
		ImGui::EndChild();

		GuiUtil::LineVertical();

		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		ImGui::BeginChild("##RightSide", ImVec2(GuiUtil::GetX(), GuiUtil::GetY()), TRUE);
		ImGui::PopStyleColor();
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGuiCol_Button ? active : inactive);
		switch (m_MenuTab)
		{
		case 0: // Features
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
			ImGui::BeginGroup();

			ImGui::CheckboxFill("No Cooldown", &vars.NoCooldown.value());

			ImGui::CheckboxFill("No Cooldown Shadow", &vars.NoCooldownShadow.value()); HELPMAKER("Enable only if you have shadow feature available");

			ImGui::CheckboxFill("God Mode", &vars.GodMode.value());

			ImGui::CheckboxFill("Damage Hack", &vars.DamageHack.value());
			if (vars.DamageHack.value())
				ImGui::DragInt("Value", &vars.DamageHackValue.value(), 10000, 100000000);

			ImGui::CheckboxFill("Dumb Enemies", &vars.DumbEnemies.value()); HELPMAKER("This will prevent enemies from attacking or moving towards you");

			// TODO:
			// Add distance check.
			// Add offset to the player position.
			ImGui::CheckboxFill("Mob Vacuum", &vars.MobVacuum.value()); HELPMAKER("You have to go to the checkpoint before killing them");
			
			ImGui::CheckboxFill("Mission Time", &vars.MissionTime.value()); HELPMAKER("Make sure this is enabled before starting a mission");
			if (vars.MissionTime.value())
				ImGui::DragInt("Time (ms)", &vars.MissionTimeMs.value(), 180000, 3600000);

			ImGui::CheckboxFill("Time Scale", &vars.TimeScale.value());
			if (vars.TimeScale.value())
				ImGui::DragFloat("Speed", &vars.TimeScaleSpeed.value(), 1.0f, 10.0f);

			ImGui::EndGroup();
			ImGui::PopStyleVar();
			break;
		case 1: // Misc
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
			ImGui::BeginGroup();

			ImGui::CheckboxFill("FPS Unlock", &vars.FPSUnlock.value());
			if (vars.FPSUnlock.value())
				ImGui::DragInt("FPS", &vars.FPSValue.value(), 5, 360);
			
			ImGui::CheckboxFill("Fov Changer", &vars.FovChanger.value());
			if (vars.FovChanger.value())
				ImGui::DragFloat("Fov", &vars.Fov.value(), 1.0f, 360.0f);

			ImGui::CheckboxFill("Skip Intro Movie", &vars.SkipIntroMovie.value()); HELPMAKER("This will skip the intro movie when you start the game");

			ImGui::CheckboxFill("Disable WebView", &vars.DisableWebView.value()); HELPMAKER("Disables WebView pop-up every time you enter the game");

			ImGui::EndGroup();
			ImGui::PopStyleVar();
			break;
		case 2: // About
			ImGui::Spacing();
			ImGui::Text("Created by: Taiga74164");
			ImGui::TextURL("Unknown Cheats thread", "https://www.unknowncheats.me/forum/other-mmorpg-and-strategy/629636-solo-leveling-arise-cheeto.html");
			break;
		}

		ImGui::PopStyleColor();
		ImGui::EndChild();
    }

    ImGui::End();
}
