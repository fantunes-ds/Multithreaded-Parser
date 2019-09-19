#pragma once

#include <Entity/Sage.h>

namespace Managers
{
    class SageManager
    {
    private:
        Entity::Sage* m_sages;
        std::thread* m_threads;
        std::mutex* m_baguetteMutexes;
        const unsigned int m_sageCountRef;
        const unsigned int m_maxMealsPerDay;
        const unsigned int m_nbOfCycles;

    public:

        SageManager(const unsigned& p_nbOfSages, const unsigned& p_maxMealsPerDay,
                    const unsigned& p_nbOfCycles);
        ~SageManager();

        void Init();
        void DisplaySageStates(Entity::Sage p_sage);

        void UpdateCycle();
    };
}
