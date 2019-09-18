#pragma once

#include <ostream>
#include <mutex>

#include <Object/Baguette.h>

namespace Entity
{
    enum SageState
    {
        IDLE,
        WAITING,
        EATING
    };

    class Sage
    {
    public :


    private :


        Object::Baguette m_baguette;

        SageState m_state{SageState::IDLE};

        int m_id{-1};

    public:

        /**
         * Thread main
         */
        Sage();
        ~Sage() = default;

        void Main(std::mutex& p_self, std::mutex& p_neighbor);
        void CheckAvailability(std::mutex& p_self, std::mutex& p_neighbor);

        const int&       GetID() const noexcept { return m_id; }
        const SageState& GetState() const noexcept { return m_state; }
        const unsigned int& GetSageCount() const noexcept;

        void SetState(const SageState& p_state) noexcept
        {
            m_state = p_state;
        }
    };

    std::ostream& operator<<(std::ostream& os, SageState s);
}
