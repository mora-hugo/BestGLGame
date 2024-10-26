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
#include <Window/BaseWindow.h>





namespace HC {
    class InputManager : public Singleton<InputManager>{
    public:
        InputManager() = default;

        InputManager(const InputManager&) = delete;
        InputManager& operator=(const InputManager&) = delete;


        void Init(class BaseWindow* context_window);


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


        std::queue<KeyboardInput> KeyboardInputs;
        std::queue<MouseInput> MouseInputs;
        std::set<int> keysInUse;
        std::set<int> keysMouseInUse;


        BaseWindow* window;
    };
}

