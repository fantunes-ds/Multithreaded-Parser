#include <Entity/Sage.h>

#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>

static unsigned int sageCount = 0;

Entity::Sage::Sage() : m_id(sageCount++)
{
    std::cout << "A new sage has joined the table. Welcome sage " << m_id << '\r';
}

void Entity::Sage::Main(std::mutex& p_self, std::mutex& p_neighbor)
{
    while (!m_isCycleOver)
    {
        CheckAvailability(p_self, p_neighbor);

        std::this_thread::sleep_for(std::chrono::milliseconds{300});
    }
    //std::cout << " m_state " << " for id " << m_id << " is now " << m_state << '\n';
}


void Entity::Sage::CheckAvailability(std::mutex& p_self, std::mutex& p_neighbor)
{
    bool isSelfAvailable{ false };
    bool isNeighbourAvailable{ false };

    if (m_state == IDLE)
    {
        std::this_thread::sleep_for(std::chrono::seconds{ 5 });
        SetState(WAITING);
    }

    if (m_state == WAITING)
    {
        isSelfAvailable = p_self.try_lock();
        isNeighbourAvailable = p_neighbor.try_lock();

        if (isSelfAvailable && isNeighbourAvailable)
        {
            SetState(EATING);
            m_eatingRecord++;

            std::this_thread::sleep_for(std::chrono::seconds{ 3 });

            SetState(IDLE);
            p_self.unlock();
            p_neighbor.unlock();
        }

        else if (!isSelfAvailable || !isNeighbourAvailable)
        {
            if (!isSelfAvailable && isNeighbourAvailable)
                p_neighbor.unlock();

            else if (isSelfAvailable && !isNeighbourAvailable)
                p_self.unlock();
        }
    }
}

const unsigned int& Entity::Sage::GetSageCount() const noexcept
{
    return sageCount;
}

std::ostream& Entity::operator<<(std::ostream& os, const SageState& s)
{
    switch (s)
    {
    case IDLE:
        os << "I";
        break;
    case WAITING:
        os << "W";
        break;
    case EATING:
        os << "E";
        break;
    default:
        os.setstate(std::ios_base::failbit);
    }
    return os;
}
