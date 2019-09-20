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

        unsigned int m_eatingRecord{0};
        bool         m_isCycleOver{false};

    public:

        /**
         * Entry point for the thread. Will run for as long as m_isCycleOver is false.
         */
        void Main(std::mutex& p_self, std::mutex& p_neighbor);

        /**
         * Checks if Sage wants to eat. If he wants to eat, he will look for chopsticks.
         * @param p_self : his chopstick(std::mutex)
         * @param p_neighbor : his neighbor chopstick(std::mutex).
         */
        void CheckAvailability(std::mutex& p_self, std::mutex& p_neighbor);

        /**
         * @return Returns the current state (enum string) of this sage.
         */
        const SageState& GetState() const noexcept { return m_state; }

        /**
         * @return Returns the amount of times this sage has eaten.
         */
        const unsigned int& GetEatingRecord() const noexcept
        {
            return m_eatingRecord;
        }

        /**
         * Sets the amount of times this sage has eaten.
         */
        void SetEatingRecord(const unsigned int& p_eatingRecord) noexcept
        {
            m_eatingRecord = p_eatingRecord;
        }

        /**
         * Thread and logic will stop if set to true.
         */
        void SetIsCycleOver(const bool& p_isCycleOver) noexcept
        {
            m_isCycleOver = p_isCycleOver;
        }

        /**
         * Changes the state for this sage.
         * @note You can specify the state directly by it's semantic value, or arithmetic.
         * @e Ex : @c 'IDLE' or @c'0' 
         */
        void SetState(const SageState& p_state) noexcept { m_state = p_state; }
    };

    std::ostream& operator<<(std::ostream& os, const SageState& s);
}
