#include "InputManager.h"
#include <Window.h>


HC::KeyboardInput::KeyboardInput(int key, int scancode, int action) : key(key), scan_code(scancode), action(
        GetKeyboardActionFromInt(action))  {

}
HC::MouseInput::MouseInput(int key, int action, const glm::vec2& position)  : key(key), action(
        GetMouseActionFromInt(action)), position(position) {

}
HC::KeyboardAction HC::KeyboardInput::GetKeyboardActionFromInt(const int action) {
    switch (action) {
        case GLFW_PRESS:
            return KeyboardAction::VP_KEY_PRESSED;
        case GLFW_RELEASE:
            return KeyboardAction::VP_KEY_RELEASED;
        case GLFW_REPEAT:
            return KeyboardAction::VP_KEY_REPEAT;
        default:
            return KeyboardAction::VP_KEY_UNKNOWN;
    }
}

HC::MouseAction HC::MouseInput::GetMouseActionFromInt(int action) {
    switch (action) {
        case GLFW_PRESS:
            return MouseAction::VP_MOUSE_PRESSED;
        case GLFW_RELEASE:
            return MouseAction::VP_MOUSE_RELEASED;
        case GLFW_REPEAT:
            return MouseAction::VP_MOUSE_REPEAT;
        case MOUSE_MOVE_INT:
            return MouseAction::VP_MOUSE_MOVE;
        default:
            return MouseAction::VP_MOUSE_UNKNOWN;
    }
}

void HC::InputManager::QueueKeyboardInput(KeyboardInput input) {
    keyboardInputs.push(input);
}

void HC::InputManager::ProcessInput() {

    // Processing REPEATING keys (Input polling)
    //TODO - Handle only keys that the user is interested in

    for(int key : keysInUse) {
        if(glfwGetKey(window->GetGLFWWindow(), key) == GLFW_PRESS) {
            KeyboardInput input(key, NO_KEY, GLFW_REPEAT);
            KeyboardEvent.Invoke(input);
        }
    }
    for(int mouseKey : keysMouseInUse) {
        if(glfwGetMouseButton(window->GetGLFWWindow(), mouseKey) == GLFW_PRESS) {
            //get mouse pos
            glm::dvec2 mousePos;
            glfwGetCursorPos(window->GetGLFWWindow(), &mousePos.x, &mousePos.y);
            MouseInput input(mouseKey, GLFW_PRESS, mousePos);
            MouseEvent.Invoke(input);
        }
    }



    // Processing PRESSED AND RELEASED keys (From window callback)
    while(!keyboardInputs.empty()) {
        const KeyboardInput& input = UnqueueKeyboardInput();
        KeyboardEvent.Invoke(input);
    }

    // Processing mouse inputs
    while(!MouseInputs.empty()) {
        const MouseInput& input = UnqueueMouseInput();
        MouseEvent.Invoke(input);
    }

}
void HC::InputManager::ListenKey(int key) {
    keysInUse.insert(key);
}

void HC::InputManager::ListenMouseKey(int key) {
    keysMouseInUse.insert(key);
}

void HC::InputManager::StopListenKey(int key) {
    keysInUse.erase(key);
}

void HC::InputManager::StopListenMouseKey(int key) {
    keysMouseInUse.erase(key);
}
const HC::KeyboardInput &HC::InputManager::UnqueueKeyboardInput() {
    const KeyboardInput& input = keyboardInputs.front();
    keyboardInputs.pop();
    return input;
}

const HC::MouseInput &HC::InputManager::UnqueueMouseInput() {
    const MouseInput& input = MouseInputs.front();
    MouseInputs.pop();
    return input;
}


bool HC::InputManager::IsKeyPressed(int key) {
    return glfwGetKey(window->GetGLFWWindow(), key) == GLFW_PRESS;
}

bool HC::InputManager::IsMouseKeyPressed(int key) {
    return glfwGetMouseButton(window->GetGLFWWindow(), key) == GLFW_PRESS;
}
void ez(HC::KeyboardInput input) {

}
void HC::InputManager::QueueMouseInput(MouseInput input) {
    MouseInputs.push(input);
}


void HC::InputManager::Init(Window* context_window) {
    window = context_window;

    window->OnWindowHandledMouseInput.AddListener(this,HC_BIND_MEMBER_FUNCTION_ARGS(&HC::InputManager::QueueMouseInput, this, 1));
    window->OnWindowHandledKeyboardInput.AddListener(this, HC_BIND_MEMBER_FUNCTION_ARGS(&HC::InputManager::QueueKeyboardInput, this, 1));
}

