#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include "InputManager.h"


namespace HC {

    class Window {
    public:
        Window(int width, int height, const std::string &windowName);
        ~Window();


        Window(const Window&) = delete;
        Window &operator=(const Window&) = delete;

        static void ImGUIFrameBegin();
        static void ImGUIRender();


        [[nodiscard]] const glm::uvec2 & GetWindowSize() const { return windowSize; }
        [[nodiscard]] const std::string & GetWindowName() const { return windowName; }
        [[nodiscard]] GLFWwindow * GetGLFWWindow() const { return window; }


    private:
        /* GLFW Callbacks */
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow *window, int button, int action, int mods);
        static void mouse_position_callback(GLFWwindow *window, double xpos, double ypos);

        void InitializeIMGUI();

    public:
        Event<KeyboardInput> OnWindowHandledKeyboardInput;
        Event<MouseInput> OnWindowHandledMouseInput;
    private:
        GLFWwindow * window;
        glm::uvec2 windowSize;
        std::string windowName;
    };

} // HC
