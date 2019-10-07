#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Rendering/Managers/InputManager.h>
#include <Rendering/Export.h>

namespace Rendering::LowRenderer
{
    class API_RENDERING Camera
    {
    public:
        Camera(const glm::vec3& p_position = glm::vec3(0.0f, 0.0f, 0.0f),
               const glm::vec3& p_up       = glm::vec3(0.0f, 1.0f, 0.0f)) noexcept;
        glm::mat4               GetViewMatrix() noexcept;
        [[nodiscard]] glm::mat4 GetProjectionMatrix() const noexcept;
        void                    Move(Managers::InputManager& p_manager) noexcept;
        void                    LookAround(
            Rendering::Managers::InputManager& p_manager);

        static std::unique_ptr<Camera>& GetInstance();
        float                           GetMovementSpeed() const;
        glm::vec3&                      GetPos() { return m_position; }
        glm::vec3&                      GetRight() { return m_rightAxis; }
        glm::vec3&                      GetUp() { return m_upAxis; }
        glm::vec3&                      GetForward() { return m_forward; }
        glm::vec3&                      GetTarget() { return m_target; }
        glm::vec3&                      GetBack() { return m_back; }
        float                           GetYaw() const { return m_yaw; }
        float                           GetPitch() const { return m_pitch; }

        void SetPos(glm::vec3& p_vec) { m_position = p_vec; }

    private:
        glm::vec3 m_position;
        glm::vec3 m_rightAxis{};
        glm::vec3 m_upAxis{};
        glm::vec3 m_forward;
        glm::vec3 m_target;
        glm::vec3 m_back;
        float     m_movementSpeed;
        float     m_yaw        = 0;
        float     m_pitch      = 0;
        bool      m_firstMouse = true;
        double    m_lastXPos;
        double    m_lastYPos;
        float     m_lookSensitivity;

        void                           UpdateCameraVector() noexcept;
        static std::unique_ptr<Camera> m_instance;
    };
}
