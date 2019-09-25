#pragma once
#include <memory>
#include <Rendering/Export.h>
#include <Rendering/Context/IWindow.h>
#include <queue>

namespace Rendering::Managers
{
    class API_RENDERING InputManager
    {
    public:
        using KeyCode = Utils::Event<int>::KeyCode;

        InputManager(const std::shared_ptr<Context::IWindow>& p_window) noexcept;
        ~InputManager() noexcept;

        bool GetKeyDown(const KeyCode& p_keyCode);
        bool GetKeyUp(const KeyCode& p_keyCode);
        bool GetKey(const KeyCode& p_keyCode);

		static std::unique_ptr<InputManager>& GetInstance();
		static void InitializeFirstInstance(const std::shared_ptr<Context::IWindow>& p_window);
        std::tuple<double, double>& GetMouseCursorPos();
        void UpdateCursorPos();
    private:
        void OnKeyPressed(const int p_key);
        void OnKeyReleased(const int p_key);
        void OnMouseButtonPressed(const int p_button);
        void OnMouseButtonReleased(const int p_button);

    private:
        std::shared_ptr<Context::IWindow> m_window;

        uint8_t m_idKeyPressedListener;
        uint8_t m_idKeyReleasedListener;
        uint8_t m_idMouseButtonPressedListener;
        uint8_t m_idMouseButtonReleasedListener;

        std::unordered_map<int, std::string> m_inputBuffer;

		static std::unique_ptr<InputManager> m_instance;
        std::tuple<double,double> m_mouseCursorPos;
    };
}
