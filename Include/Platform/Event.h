#pragma once

#include <functional>
#include <vector>
#include <map>

// This is a macro that generates a function pointer to a member function of a class without writing any placeholders.
#define HC_BIND_MEMBER_FUNCTION_ARGS(function_ptr, instance_ptr, num_args) \
    std::bind(function_ptr, instance_ptr, BIND_MEMBER_FUNCTION_PLACEHOLDERS_##num_args)

#define BIND_MEMBER_FUNCTION_PLACEHOLDERS_0
#define BIND_MEMBER_FUNCTION_PLACEHOLDERS_1 std::placeholders::_1
#define BIND_MEMBER_FUNCTION_PLACEHOLDERS_2 std::placeholders::_1, std::placeholders::_2
#define BIND_MEMBER_FUNCTION_PLACEHOLDERS_3 std::placeholders::_1, std::placeholders::_2, std::placeholders::_3
#define BIND_MEMBER_FUNCTION_PLACEHOLDERS_4 std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4
#define BIND_MEMBER_FUNCTION_PLACEHOLDERS_5 std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5

namespace HC {

    template <typename ...Args>
    class Event {
    public:
        Event() = default;
        virtual ~Event() = default;

        Event(const Event&) = delete;
        Event& operator=(const Event&) = delete;

        void AddListener(const void* ownerPtr, std::function<void(Args...)> func) {
            listeners[reinterpret_cast<std::uintptr_t>(ownerPtr)] = std::move(func);
        }

        void RemoveListener(const void* ownerPtr) {
            auto it = listeners.find(reinterpret_cast<std::uintptr_t>(ownerPtr));
            if (it != listeners.end()) {
                listeners.erase(it);
            }
        }

        void ClearListeners() {
            listeners.clear();
        }

        void Invoke(Args... args) const {
            for (const auto& listener : listeners) {
                listener.second(args...);
            }
        }

    private:
        struct KeyComparer {
            bool operator()(std::uintptr_t lhs, std::uintptr_t rhs) const {
                return lhs < rhs;
            }
        };

        std::map<std::uintptr_t, std::function<void(Args...)>, KeyComparer> listeners;
    };

} // namespace HC
