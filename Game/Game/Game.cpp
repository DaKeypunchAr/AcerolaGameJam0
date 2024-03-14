#include "Game.h"

#include "GLFW/glfw3.h"

#include <iostream>

namespace Game
{
	Game::Game()
		: cam(windowDimension), atlas("Resources/Fonts/teeny-tiny-font.ttf"), floorManager(this), player(this), ui(this)
	{
        uiColorProgram.initialize("Resources/Shaders/UI-Color");
        uiTextureProgram.initialize("Resources/Shaders/UI-Texture");
        textProgram.initialize("Resources/Shaders/Text");
        gameTextureProgram.initialize("Resources/Shaders/Game-Texture");

        soloud.init();
        death.load("Resources/Sounds/death.wav");
        menu.load("Resources/Sounds/menu.wav");
        jump.load("Resources/Sounds/jump.wav");
        beep.load("Resources/Sounds/doublebeep.wav");
	}

	void Game::draw()
	{
        if (state == GameState::PLAY || state == GameState::PAUSE)
        {
            player.draw(gameTextureProgram, cam);
            floorManager.drawFloors(cam);
        }
		ui.drawUI();
	}

	void Game::update()
	{
		double dt = glfwGetTime() - lastTick;

        if (state == GameState::PLAY)
        {
            if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE))
            {
                if (!waitCounter)
                {
                    waitCounter = 20;
                    state = GameState::PAUSE;
                    menuIdx = 0;
                }
            }

            floorManager.update(dt);
            player.update(dt);

            if (twistTimer == glm::ivec2(0))
            {
                beeped = 0;
                twistTimer = randomTime();
                leftButton = randomKey();
                rightButton = randomKey();
                while (rightButton == leftButton) rightButton = randomKey();
                jumpButton = randomKey();
                while (jumpButton == leftButton || jumpButton == rightButton) jumpButton = randomKey();
            }

            if (cam.getTranslation() != camTranslation)
            {
                if (lastTranslation == glm::vec2(3.0f, 0.0f))
                {
                    lastCameraMoveTime = glfwGetTime();
                    lastTranslation = cam.getTranslation();
                }
                else
                {
                    auto lerp = [](const glm::vec2& a, const glm::vec2& b, float t) {
                        return (1.0f - t) * a + t * b;
                        };
                    cam.setTranslation(lerp(lastTranslation, camTranslation, (float)((glfwGetTime() - lastCameraMoveTime) * (glfwGetTime() - lastCameraMoveTime))));
                }
                if (((glfwGetTime() - lastCameraMoveTime) * (glfwGetTime() - lastCameraMoveTime)) > 1)
                {
                    lastTranslation = glm::vec2(3.0f, 0.0f);
                    cam.setTranslation(camTranslation);
                }
            }
        }
        else if (state == GameState::MAIN_MENU)
        {
            if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE))
            {
                if (!waitCounter)
                {
                    glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
                }
            }
            if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W))
            {
                if (!upPressed)
                {
                    if (menuIdx) soloud.play(menu);
                    menuIdx--;
                    upPressed = true;
                }
            }
            else upPressed = false;
            if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S))
            {
                if (!downPressed)
                {
                    if (menuIdx != 2) soloud.play(menu);
                    menuIdx++;
                    downPressed = true;
                }
            }
            else downPressed = false;
            if (menuIdx < 0) menuIdx = 0;
            else if (menuIdx > 2) menuIdx = 2;

            if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ENTER))
            {
                if (!waitCounter)
                {
                    soloud.play(menu);
                    waitCounter = 20;
                    if (menuIdx == 0)
                    {
                        floorManager.restart();
                        player.restart();
                        lastTranslation = camTranslation;
                        camTranslation.y = 0;
                        leftButton = GLFW_KEY_A;
                        rightButton = GLFW_KEY_D;
                        jumpButton = GLFW_KEY_SPACE;
                        glm::ivec2 twistTimer = randomTime();
                        state = GameState::PLAY;
                    }
                    if (menuIdx == 1) state = GameState::ABOUT;
                    if (menuIdx == 2) glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
                }
            }
        }
        else if (state == GameState::ABOUT)
        {
            if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ENTER))
            {
                if (!waitCounter)
                {
                    soloud.play(menu);
                    state = GameState::MAIN_MENU;
                    waitCounter = 20;
                }
            }
            
        }
        else if (state == GameState::PAUSE || state == GameState::END)
        {
            if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE))
            {
                if (!waitCounter)
                {
                    state = (state == GameState::PAUSE) ? GameState::PLAY : GameState::MAIN_MENU;
                    waitCounter = 20;
                }
            }
            if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R))
            {
                soloud.play(menu);
                floorManager.restart();
                player.restart();
                cam.setTranslation(glm::vec2(0));
                leftButton = GLFW_KEY_A;
                rightButton = GLFW_KEY_D;
                jumpButton = GLFW_KEY_SPACE;
                twistTimer = randomTime();
                state = GameState::PLAY;
            }

            if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ENTER))
            {
                if (!waitCounter)
                {
                    waitCounter = 20;
                    state = GameState::MAIN_MENU;
                }
            }
        }

        --waitCounter;
        if (waitCounter < 0) waitCounter = 0;

        ui.updateUI(dt);

		lastTick = glfwGetTime();
	}

	glm::ivec2 Game::randomTime() const
	{
		// Constants for duration range and mean
		const int minSeconds = 10;
		const int maxSeconds = 120; // 2 minutes
		const int meanSeconds = (minSeconds + maxSeconds) / 2;

		// Random number generator
		std::random_device rd;
		std::mt19937 gen(rd());
		std::normal_distribution<double> distrib(meanSeconds, (maxSeconds - minSeconds) / 3.0); // Standard deviation is 1/3 of the range

		// Generate a random duration in seconds
		int seconds;
		do {
			seconds = static_cast<int>(distrib(gen));
		} while (seconds < minSeconds || seconds > maxSeconds);

		// Convert seconds to minutes and seconds
		int minutes = seconds / 60;
		seconds %= 60;

		return glm::ivec2(minutes, seconds);
	}
	unsigned int Game::randomKey() const
	{
        std::vector<int> keys = {
            GLFW_KEY_SPACE, GLFW_KEY_APOSTROPHE, GLFW_KEY_COMMA, GLFW_KEY_MINUS,
            GLFW_KEY_PERIOD, GLFW_KEY_SLASH, GLFW_KEY_0, GLFW_KEY_1, GLFW_KEY_2,
            GLFW_KEY_3, GLFW_KEY_4, GLFW_KEY_5, GLFW_KEY_6, GLFW_KEY_7, GLFW_KEY_8,
            GLFW_KEY_9, GLFW_KEY_SEMICOLON, GLFW_KEY_EQUAL, GLFW_KEY_A, GLFW_KEY_B,
            GLFW_KEY_C, GLFW_KEY_D, GLFW_KEY_E, GLFW_KEY_F, GLFW_KEY_G, GLFW_KEY_H,
            GLFW_KEY_I, GLFW_KEY_J, GLFW_KEY_K, GLFW_KEY_L, GLFW_KEY_M, GLFW_KEY_N,
            GLFW_KEY_O, GLFW_KEY_P, GLFW_KEY_Q, GLFW_KEY_R, GLFW_KEY_S, GLFW_KEY_T,
            GLFW_KEY_U, GLFW_KEY_V, GLFW_KEY_W, GLFW_KEY_X, GLFW_KEY_Y, GLFW_KEY_Z,
            GLFW_KEY_ESCAPE, GLFW_KEY_ENTER, GLFW_KEY_TAB, GLFW_KEY_BACKSPACE,
            GLFW_KEY_LEFT_SHIFT, GLFW_KEY_LEFT_CONTROL, GLFW_KEY_LEFT_ALT,
            GLFW_KEY_RIGHT_SHIFT, GLFW_KEY_RIGHT_CONTROL, GLFW_KEY_RIGHT_ALT
        };

        // Random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, keys.size() - 1);

        // Generate random index
        int randomIndex = distribution(gen);

        // Return random key
        return keys[randomIndex];
	}
    std::string Game::getKeyName(unsigned int key) const
    {
        switch (key) {
        case GLFW_KEY_SPACE:
            return "Space";
        case GLFW_KEY_APOSTROPHE:
            return "'";
        case GLFW_KEY_COMMA:
            return ",";
        case GLFW_KEY_MINUS:
            return "-";
        case GLFW_KEY_PERIOD:
            return ".";
        case GLFW_KEY_SLASH:
            return "/";
        case GLFW_KEY_0:
            return "0";
        case GLFW_KEY_1:
            return "1";
        case GLFW_KEY_2:
            return "2";
        case GLFW_KEY_3:
            return "3";
        case GLFW_KEY_4:
            return "4";
        case GLFW_KEY_5:
            return "5";
        case GLFW_KEY_6:
            return "6";
        case GLFW_KEY_7:
            return "7";
        case GLFW_KEY_8:
            return "8";
        case GLFW_KEY_9:
            return "9";
        case GLFW_KEY_SEMICOLON:
            return ";";
        case GLFW_KEY_EQUAL:
            return "=";
        case GLFW_KEY_A:
            return "A";
        case GLFW_KEY_B:
            return "B";
        case GLFW_KEY_C:
            return "C";
        case GLFW_KEY_D:
            return "D";
        case GLFW_KEY_E:
            return "E";
        case GLFW_KEY_F:
            return "F";
        case GLFW_KEY_G:
            return "G";
        case GLFW_KEY_H:
            return "H";
        case GLFW_KEY_I:
            return "I";
        case GLFW_KEY_J:
            return "J";
        case GLFW_KEY_K:
            return "K";
        case GLFW_KEY_L:
            return "L";
        case GLFW_KEY_M:
            return "M";
        case GLFW_KEY_N:
            return "N";
        case GLFW_KEY_O:
            return "O";
        case GLFW_KEY_P:
            return "P";
        case GLFW_KEY_Q:
            return "Q";
        case GLFW_KEY_R:
            return "R";
        case GLFW_KEY_S:
            return "S";
        case GLFW_KEY_T:
            return "T";
        case GLFW_KEY_U:
            return "U";
        case GLFW_KEY_V:
            return "V";
        case GLFW_KEY_W:
            return "W";
        case GLFW_KEY_X:
            return "X";
        case GLFW_KEY_Y:
            return "Y";
        case GLFW_KEY_Z:
            return "Z";
        case GLFW_KEY_LEFT_BRACKET:
            return "[";
        case GLFW_KEY_BACKSLASH:
            return "\\";
        case GLFW_KEY_RIGHT_BRACKET:
            return "]";
        case GLFW_KEY_GRAVE_ACCENT:
            return "`";

            // Special keys
        case GLFW_KEY_ESCAPE:
            return "Escape";
        case GLFW_KEY_ENTER:
            return "Enter";
        case GLFW_KEY_TAB:
            return "Tab";
        case GLFW_KEY_BACKSPACE:
            return "Backspace";
        case GLFW_KEY_INSERT:
            return "Insert";
        case GLFW_KEY_DELETE:
            return "Delete";
        case GLFW_KEY_RIGHT:
            return "Right";
        case GLFW_KEY_LEFT:
            return "Left";
        case GLFW_KEY_DOWN:
            return "Down";
        case GLFW_KEY_UP:
            return "Up";
        case GLFW_KEY_PAGE_UP:
            return "Page Up";
        case GLFW_KEY_PAGE_DOWN:
            return "Page Down";
        case GLFW_KEY_HOME:
            return "Home";
        case GLFW_KEY_END:
            return "End";
        case GLFW_KEY_CAPS_LOCK:
            return "Caps Lock";
        case GLFW_KEY_NUM_LOCK:
            return "Num Lock";
        case GLFW_KEY_PRINT_SCREEN:
            return "Print Screen";
        case GLFW_KEY_PAUSE:
            return "Pause";
        case GLFW_KEY_F1:
            return "F1";
        case GLFW_KEY_F2:
            return "F2";
        case GLFW_KEY_F3:
            return "F3";
        case GLFW_KEY_F4:
            return "F4";
        case GLFW_KEY_F5:
            return "F5";
        case GLFW_KEY_F6:
            return "F6";
        case GLFW_KEY_F7:
            return "F7";
        case GLFW_KEY_F8:
            return "F8";
        case GLFW_KEY_F9:
            return "F9";
        case GLFW_KEY_F10:
            return "F10";
        case GLFW_KEY_F11:
            return "F11";
        case GLFW_KEY_F12:
            return "F12";
        case GLFW_KEY_LEFT_SHIFT:
            return "Left Shift";
        case GLFW_KEY_LEFT_CONTROL:
            return "Left Control";
        case GLFW_KEY_LEFT_ALT:
            return "Left Alt";
        case GLFW_KEY_LEFT_SUPER:
            return "Left Super";
        case GLFW_KEY_RIGHT_SHIFT:
            return "Right Shift";
        case GLFW_KEY_RIGHT_CONTROL:
            return "Right Control";
        case GLFW_KEY_RIGHT_ALT:
            return "Right Alt";
        case GLFW_KEY_RIGHT_SUPER:
            return "Right Super";
        case GLFW_KEY_MENU:
            return "Menu";

        default:
            return "Unknown";
        }
    }
    std::string Game::getScore() const
    {
        std::string score = "Score: ";

        auto ansIn4Digit = [&](int i)
            {
                if (i < 10) return std::string("000") + std::to_string(i);
                else if (i < 100) return std::string("00") + std::to_string(i);
                else if (i < 1000) return std::string("0") + std::to_string(i);
                else return std::to_string(i);
            };

        return score + ansIn4Digit(cam.getTranslation().y / -25.0f);
    }

	/* normalizeScreenSpace() is in Entity.cpp */

	glm::uvec2 Game::windowDimension = glm::uvec2(1920, 1032);
}