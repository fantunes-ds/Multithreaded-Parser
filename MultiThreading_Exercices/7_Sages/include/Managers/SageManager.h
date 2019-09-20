#pragma once

#include <Entity/Sage.h>
#include <vector>
#include <deque>

namespace Managers
{
    class SageManager
    {
    private:
        const unsigned int m_sageCount{0};
        const unsigned int m_maxMealsPerDay{3};
        const unsigned int m_nbOfCycles{7};

        std::vector<Entity::Sage> m_sages{};
        std::vector<std::thread>  m_threads{};
        std::deque<std::mutex>    m_baguetteMutexes{};
    public:

        SageManager(const unsigned& p_nbOfSages, const unsigned& p_maxMealsPerDay,
                    const unsigned& p_nbOfCycles);
        ~SageManager() = default;

        void Init();
        void DisplaySageStates(const Entity::Sage& p_sage);

        void UpdateCycle();
    };
}
