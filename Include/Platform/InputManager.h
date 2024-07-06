#pragma once
#include <queue>
#include <map>
#include <unordered_map>
#include <functional>
#include <string>
#include <glm/vec2.hpp>
#include <Singleton.h>
#include <Event.h>
#include <set>



#define NO_KEY -1

namespace HC {
    enum class KeyboardAction {
        VP_KEY_PRESSED,
        VP_KEY_RELEASED,
        VP_KEY_REPEAT,
        VP_KEY_UNKNOWN
    };

    enum class MouseAction {
        VP_MOUSE_PRESSED,
        VP_MOUSE_RELEASED,
        VP_MOUSE_REPEAT,
        VP_MOUSE_MOVE,
        VP_MOUSE_UNKNOWN
    };


    struct KeyboardInput {
    public:
        KeyboardInput() = default;
        KeyboardInput(int key, int scancode, int action);
        KeyboardInput(const KeyboardInput&) = default;
        KeyboardInput &operator=(const KeyboardInput&) = delete;

    private:
        static KeyboardAction GetKeyboardActionFromInt(int action);

    public:
        int key = NO_KEY;
        int scan_code = NO_KEY;
        KeyboardAction action = KeyboardAction::VP_KEY_UNKNOWN;


    };


    struct MouseInput {
    public:
        MouseInput() = default;
        MouseInput(int key, int action, const glm::vec2& position);
        MouseInput(const MouseInput&) = default;
        MouseInput &operator=(const MouseInput&) = delete;

    private:
        static MouseAction GetMouseActionFromInt(int action);

    public:
        int key = NO_KEY;
        glm::vec2 position = glm::vec2(0.0f);
        const inline static int MOUSE_MOVE_INT = 3;


        MouseAction action = MouseAction::VP_MOUSE_UNKNOWN;


    };

    class InputManager : public Singleton<InputManager>{

    public:
        InputManager() = default;

        InputManager(const InputManager&) = delete;
        InputManager& operator=(const InputManager&) = delete;


        void Init(class Window* context_window);


        //TODO : Better way to handle reapeat keys
        void ListenKey(int key);
        void ListenMouseKey(int key);
        void StopListenKey(int key);
        void StopListenMouseKey(int key);

        /* Keyboard */
        void QueueKeyboardInput(KeyboardInput input);

        /* Mouse */
        void QueueMouseInput(MouseInput);

        void ProcessInput();

        bool IsKeyPressed(int key);
        bool IsMouseKeyPressed(int key);
    private:

        const KeyboardInput& UnqueueKeyboardInput();
        const MouseInput& UnqueueMouseInput();

    public:
        Event<KeyboardInput> KeyboardEvent;
        Event<MouseInput> MouseEvent;

    private:


        std::queue<KeyboardInput> keyboardInputs;
        std::queue<MouseInput> MouseInputs;
        std::set<int> keysInUse;
        std::set<int> keysMouseInUse;


        class Window* window;
    };
}

