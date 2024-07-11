#pragma once

#include <memory>
#include <chrono>
#include "InputManager.h"

namespace HC {
    class Window;
    class GameLayer;
    class App {
    public:
        App();
        ~App();
        int Run();
        float CalculateDeltaTime();

        [[nodiscard]] glm::vec2 GetWindowSize() const;

    private:
        std::unique_ptr<Window> window;
        std::unique_ptr<GameLayer> gameLayer;

        /* Delta time */
        std::chrono::time_point<std::chrono::steady_clock> currentTime;
        std::chrono::time_point<std::chrono::steady_clock> previousTime;


    };
}