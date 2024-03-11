#include "Game.h"

#include "GLFW/glfw3.h"

#include <iostream>

namespace Game
{
	Game::Game()
		: cam(glm::vec2(0, windowDimension.x), glm::vec2(0, windowDimension.y)), atlas("Resources/Fonts/teeny-tiny-font.ttf"), player(this), ui(this)
	{
		colorProgram.initialize("Resources/Shaders/Color");
		textureProgram.initialize("Resources/Shaders/Texture");
		textProgram.initialize("Resources/Shaders/Text");
	}

	void Game::draw()
	{
		player.draw(textureProgram);
		floorManager.drawFloors();
		ui.drawUI();
	}

	void Game::update()
	{
		double dt = glfwGetTime() - lastTick;

		floorManager.update(dt);
		player.update(dt);
		ui.updateUI(dt);

		if (twistTimer == glm::ivec2(0))
		{
			twistTimer = randomTime();
            leftButton = randomKey();
            rightButton = randomKey();
            while (rightButton == leftButton) rightButton = randomKey();
            jumpButton = randomKey();
            while (jumpButton == leftButton || jumpButton == rightButton) jumpButton = randomKey();
		}

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
        std::vector<int> laptopKeys = {
            GLFW_KEY_SPACE,
            GLFW_KEY_APOSTROPHE,
            GLFW_KEY_COMMA,
            GLFW_KEY_MINUS,
            GLFW_KEY_PERIOD,
            GLFW_KEY_SLASH,
            GLFW_KEY_0,
            GLFW_KEY_1,
            GLFW_KEY_2,
            GLFW_KEY_3,
            GLFW_KEY_4,
            GLFW_KEY_5,
            GLFW_KEY_6,
            GLFW_KEY_7,
            GLFW_KEY_8,
            GLFW_KEY_9,
            GLFW_KEY_SEMICOLON,
            GLFW_KEY_EQUAL,
            GLFW_KEY_A,
            GLFW_KEY_B,
            GLFW_KEY_C,
            GLFW_KEY_D,
            GLFW_KEY_E,
            GLFW_KEY_F,
            GLFW_KEY_G,
            GLFW_KEY_H,
            GLFW_KEY_I,
            GLFW_KEY_J,
            GLFW_KEY_K,
            GLFW_KEY_L,
            GLFW_KEY_M,
            GLFW_KEY_N,
            GLFW_KEY_O,
            GLFW_KEY_P,
            GLFW_KEY_Q,
            GLFW_KEY_R,
            GLFW_KEY_S,
            GLFW_KEY_T,
            GLFW_KEY_U,
            GLFW_KEY_V,
            GLFW_KEY_W,
            GLFW_KEY_X,
            GLFW_KEY_Y,
            GLFW_KEY_Z,
            GLFW_KEY_LEFT_BRACKET,
            GLFW_KEY_BACKSLASH,
            GLFW_KEY_RIGHT_BRACKET,
            GLFW_KEY_GRAVE_ACCENT,
            GLFW_KEY_ESCAPE,
            GLFW_KEY_ENTER,
            GLFW_KEY_TAB,
            GLFW_KEY_BACKSPACE,
            GLFW_KEY_INSERT,
            GLFW_KEY_DELETE,
            GLFW_KEY_RIGHT,
            GLFW_KEY_LEFT,
            GLFW_KEY_DOWN,
            GLFW_KEY_UP,
            GLFW_KEY_PAGE_UP,
            GLFW_KEY_PAGE_DOWN,
            GLFW_KEY_HOME,
            GLFW_KEY_END,
            GLFW_KEY_CAPS_LOCK,
            GLFW_KEY_NUM_LOCK,
            GLFW_KEY_PRINT_SCREEN,
            GLFW_KEY_PAUSE,
            GLFW_KEY_LEFT_SHIFT,
            GLFW_KEY_LEFT_CONTROL,
            GLFW_KEY_LEFT_ALT,
            GLFW_KEY_LEFT_SUPER,
            GLFW_KEY_RIGHT_SHIFT,
            GLFW_KEY_RIGHT_CONTROL,
            GLFW_KEY_RIGHT_ALT,
            GLFW_KEY_RIGHT_SUPER,
            GLFW_KEY_MENU
        };

        // Random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(0, laptopKeys.size() - 1);

        // Choose a random key from the list
        return laptopKeys[distrib(gen)];
	}
    std::string Game::getKeyName(unsigned int key) const
    {
        switch (key) {
            // Printable keys
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

	/* normalizeScreenSpace() is in Entity.cpp */

	glm::uvec2 Game::windowDimension = glm::uvec2(1920, 1032);
}