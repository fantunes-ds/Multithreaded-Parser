#pragma once

#include <Entity/Sage.h>
#include <vector>
#include <deque>

namespace Managers
{
    
    // This class manipulates Entity::Sage classes and their cycle.
    class SageManager
    {
    private:
        const unsigned int m_sageCount{0};
        const unsigned int m_maxMealsPerDay{3};
        const unsigned int m_nbOfCycles{7};

        std::vector<Entity::Sage> m_sages{};
        std::vector<std::thread>  m_threads{};

        /// Since std::vector requires a copy constructor/move and std::mutex
        /// doesn't have one we use a std::deque instead, since we are only
        /// going to emplace back. It poses no problems.
        std::deque<std::mutex>    m_baguetteMutexes{};
    public:

        /**
         * The Constructor defines how many sages are created,
         * how many times they eat per day, as well as
         * for how long (in days) they will be eating.
         */
        SageManager(const unsigned& p_nbOfSages, const unsigned& p_maxMealsPerDay,
                    const unsigned& p_nbOfCycles); 

        ~SageManager() = default;

        // Starts the logic
        void Init();

        /**
         * Displays in one character the state of the given sage
         * @param p_sage : The sage you want to display info from.
         */
        void DisplaySageStates(const Entity::Sage& p_sage);

        /**
         * Runs the logic for cycles.
         */
        void UpdateCycle();
    };
}
