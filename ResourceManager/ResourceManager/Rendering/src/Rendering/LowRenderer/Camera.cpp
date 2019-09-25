#include <stdafx.h>
#include <Rendering/LowRenderer/Camera.h>

using namespace Rendering::LowRenderer;

std::unique_ptr<Camera> Camera::m_instance;

Camera::Camera(const glm::vec3& p_position, const glm::vec3& p_up) noexcept
    : m_position{ glm::vec3(0.0f, 0.0f, 3.0f) },
    m_rightAxis{ glm::vec3{1.0f, 0.0f, 0.0f } },
    m_upAxis{ glm::vec3{0.0f, 1.0f, 0.0f} },
    m_forward{ glm::vec3(0.0f, 0.0f, -1.0f) },
    m_target{ glm::vec3(0.0f, 0.0f, 0.0f) },
	m_movementSpeed{ 0.005f }
{
    UpdateCameraVector();
}


void Camera::UpdateCameraVector() noexcept
{
    //m_back      = normalize(m_position - m_target);
    m_forward   = -m_back;
    m_rightAxis = normalize(cross(m_upAxis, m_back));
    //m_upAxis    = normalize(cross(m_back, m_rightAxis));
}

glm::mat4 Camera::GetViewMatrix() noexcept
{
    UpdateCameraVector();
    return lookAt(m_position, m_position - m_back, m_upAxis);
}

glm::mat4 Camera::GetProjectionMatrix() const noexcept
{
    return glm::perspective(glm::radians(60.0f), static_cast<float>(1920) / static_cast<float>(1080), 0.1f, 100.0f);;
}

void Camera::Move(Rendering::Managers::InputManager& p_manager) noexcept
{
    // Need deltaTime here
    if (p_manager.GetKey(Utils::Event<int>::KeyCode::W))
    {
        m_position += m_movementSpeed * m_forward;
    }
    if (p_manager.GetKey(Utils::Event<int>::KeyCode::S))
    {
        m_position -= m_movementSpeed * m_forward;
    }
    if (p_manager.GetKey(Utils::Event<int>::KeyCode::A))
    {
        m_position -= normalize(cross(m_forward, m_upAxis)) * m_movementSpeed;
    }
    if (p_manager.GetKey(Utils::Event<int>::KeyCode::D))
    {
        m_position += normalize(cross(m_forward, m_upAxis)) * m_movementSpeed;
    }
	if (p_manager.GetKey(Utils::Event<int>::KeyCode::Space))
	{
		m_position += m_movementSpeed * m_upAxis;
	}
	if (p_manager.GetKey(Utils::Event<int>::KeyCode::C))
	{
		m_position -= m_movementSpeed * m_upAxis;
	}
}

void Camera::LookAround(Rendering::Managers::InputManager& p_manager)
{
    std::tuple mousePos = p_manager.GetMouseCursorPos();

    if (m_firstMouse) // this bool variable is initially set to true
    {
        m_lastXPos = std::get<0>(mousePos);
        m_lastYPos = std::get<1>(mousePos);
        m_firstMouse = false;
        return;
    }

    double xoffset = std::get<0>(mousePos) - m_lastXPos;
    double yoffset = std::get<1>(mousePos) - m_lastYPos; // reversed since y-coordinates range from bottom to top
    m_lastXPos = std::get<0>(mousePos);
    m_lastYPos = std::get<1>(mousePos);

    m_lookSensitivity = 0.05f;
    xoffset *= m_lookSensitivity;
    yoffset *= m_lookSensitivity;

    m_yaw += static_cast<float>(xoffset);
    m_pitch += static_cast<float>(yoffset);

    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
    front.y = sin(glm::radians(m_pitch));
    front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
    m_back = normalize(front);
}


std::unique_ptr<Camera>& Camera::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = std::make_unique<Camera>();
    }

    return m_instance;
}

float Camera::GetMovementSpeed() const { return m_movementSpeed; }
