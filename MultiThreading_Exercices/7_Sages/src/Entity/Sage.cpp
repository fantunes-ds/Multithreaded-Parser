#include <Entity/Sage.h>

#include <thread>
#include <iostream>
#include <chrono>

static unsigned int sageCount = 0;

Entity::Sage::Sage() : m_id(sageCount++)
{
    std::cout << "A new sage has joined the table. Welcome sage " << m_id << '\r';
}

void Entity::Sage::Main()
{
    while (true)
    {
        if (m_state != EATING)
            m_state = EATING;
        else
            m_state = WAITING;

        std::this_thread::sleep_for(std::chrono::seconds{1});
    }

    //std::cout << " m_state " << " for id " << m_id << " is now " << m_state << '\n';
}

const unsigned int Entity::Sage::GetSageCount() const noexcept
{
    return sageCount;
}

std::ostream& Entity::operator<<(std::ostream& os, SageState s)
{
    switch (s)
    {
    case IDLE:
        os << "S";
        break;
    case WAITING:
        os << "A";
        break;
    case EATING:
        os << "M";
        break;
    default:
        os.setstate(std::ios_base::failbit);
    }
    return os;
}
