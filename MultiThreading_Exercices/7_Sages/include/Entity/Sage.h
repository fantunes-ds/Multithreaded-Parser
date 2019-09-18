#pragma once
#include <ostream>

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

        SageState m_state{SageState::IDLE};

        int m_id{-1};

    public:

        /**
         * Thread main
         */
        Sage();
        ~Sage() = default;

        void Main(void);

        const int       GetID() const noexcept { return m_id; }
        SageState GetState() const noexcept { return m_state; }
        const unsigned int GetSageCount() const noexcept;

        void SetState(const SageState p_state) noexcept
        {
            m_state = p_state;
        }
    };

    std::ostream& operator<<(std::ostream& os, SageState s);
}
