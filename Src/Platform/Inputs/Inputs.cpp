#include "Inputs/Inputs.h"
#include "GLFW/glfw3.h"

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

