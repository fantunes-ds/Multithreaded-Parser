#pragma once

#include <ostream>
#include <mutex>

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
    private :
        SageState m_state{IDLE};

        int          m_id{-1};
        unsigned int m_eatingRecord{0};
        bool         m_isCycleOver{false};

    public:

        /**
         * Thread main
         */
        Sage();
        ~Sage() = default;

        void Main(std::mutex& p_self, std::mutex& p_neighbor);
        void CheckAvailability(std::mutex& p_self, std::mutex& p_neighbor);

        const int&          GetID() const noexcept { return m_id; }
        const SageState&    GetState() const noexcept { return m_state; }
        const unsigned int& GetSageCount() const noexcept;

        const unsigned int& GetEatingRecord() const noexcept
        {
            return m_eatingRecord;
        }


        void SetEatingRecord(const unsigned int& p_eatingRecord) noexcept
        {
            m_eatingRecord = p_eatingRecord;
        }
        void SetIsCycleOver(const bool& p_isCycleOver) noexcept
        {
            m_isCycleOver = p_isCycleOver;
        }

        void SetState(const SageState& p_state) noexcept { m_state = p_state; }
    };

    std::ostream& operator<<(std::ostream& os, const SageState& s);
}
