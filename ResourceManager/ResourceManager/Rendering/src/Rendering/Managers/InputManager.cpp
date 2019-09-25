#include <stdafx.h>
#include <Rendering/Managers/InputManager.h>

std::unique_ptr<Rendering::Managers::InputManager> Rendering::Managers::InputManager::m_instance;

Rendering::Managers::InputManager::InputManager(
	const std::shared_ptr<Context::IWindow>& p_window) noexcept : m_window{ p_window }
{
    m_idKeyPressedListener = p_window->m_keyPressedEvent.AddListener(std::bind(&InputManager::OnKeyPressed, this,
                                                                               std::placeholders::_1));
    m_idKeyReleasedListener = p_window->m_keyReleasedEvent.AddListener(std::bind(&InputManager::OnKeyReleased, this,
                                                                                 std::placeholders::_1));
    m_idMouseButtonPressedListener = p_window->m_mouseButtonPressedEvent.
                                               AddListener(std::bind(&InputManager::OnMouseButtonPressed, this,
                                                                     std::placeholders::_1));
    m_idMouseButtonReleasedListener = p_window->m_mouseButtonReleasedEvent.
                                                AddListener(std::bind(&InputManager::OnMouseButtonReleased, this,
                                                                      std::placeholders::_1));
    glfwSetInputMode(std::any_cast<GLFWwindow*>(p_window->Data()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_mouseCursorPos = std::make_tuple(0.0, 0.0);
}

Rendering::Managers::InputManager::~InputManager() noexcept
{
    assert(m_window->m_keyPressedEvent.RemoveListener(m_idKeyPressedListener));
    assert(m_window->m_keyReleasedEvent.RemoveListener(m_idKeyReleasedListener));
    assert(m_window->m_mouseButtonPressedEvent.
                     RemoveListener(m_idMouseButtonPressedListener));
    assert(m_window->m_mouseButtonReleasedEvent.
                     RemoveListener(m_idMouseButtonReleasedListener));
}

bool Rendering::Managers::InputManager::GetKeyDown(const KeyCode& p_keyCode)
{
    if (!(m_inputBuffer.find(p_keyCode) == m_inputBuffer.end()))
        if (m_inputBuffer.find(p_keyCode)->second == "KeyDown") 
        {
            m_inputBuffer.at(p_keyCode) = "Complete";
            return true;
        }
    return false;

}

bool Rendering::Managers::InputManager::GetKeyUp(const KeyCode& p_keyCode)
{
    if (!(m_inputBuffer.find(p_keyCode) == m_inputBuffer.end()))
        if (m_inputBuffer.find(p_keyCode)->second == "KeyUp")
        {
            m_inputBuffer.at(p_keyCode) = "Complete";
            return true;
        }
    return false;
}

bool Rendering::Managers::InputManager::GetKey(const KeyCode& p_keyCode)
{
    if (!(m_inputBuffer.find(p_keyCode) == m_inputBuffer.end()))
        if (m_inputBuffer.find(p_keyCode)->second == "KeyDown")
            return true;
    return false;
}

std::tuple<double, double>& Rendering::Managers::InputManager::GetMouseCursorPos()
{
	return m_mouseCursorPos;
}

std::unique_ptr<Rendering::Managers::InputManager>& Rendering::Managers::InputManager::GetInstance()
{
	assert(m_instance != nullptr);
	return m_instance;
}

void Rendering::Managers::InputManager::InitializeFirstInstance(const std::shared_ptr<Context::IWindow>& p_window)
{
	m_instance = std::make_unique<InputManager>(p_window);
}

void Rendering::Managers::InputManager::OnKeyPressed(const int p_key)
{
	//std::cout << "Key Pressed : " << p_key << '\n';
	m_inputBuffer.insert_or_assign(p_key, "KeyDown");
}

void Rendering::Managers::InputManager::OnKeyReleased(const int p_key)
{
	//std::cout << "Key Released : " << p_key << '\n';
	m_inputBuffer.insert_or_assign(p_key, "KeyUp");
}

void Rendering::Managers::InputManager::OnMouseButtonPressed(const int p_button)
{
	//std::cout << "Mouse Button Pressed : " << p_button << '\n';
}

void Rendering::Managers::InputManager::OnMouseButtonReleased(const int p_button)
{
	//std::cout << "Mouse Button Released : " << p_button << '\n';
}

void Rendering::Managers::InputManager::UpdateCursorPos()
{
    glfwGetCursorPos(std::any_cast<GLFWwindow*>(m_window->Data()), &std::get<0>(m_mouseCursorPos), &std::get<1>(m_mouseCursorPos));
}
