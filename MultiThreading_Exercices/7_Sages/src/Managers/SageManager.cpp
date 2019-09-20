#include <Managers/SageManager.h>
#include <iostream>

using namespace Entity;

Managers::SageManager::SageManager(const unsigned int& p_nbOfSages,
                                   const unsigned int& p_maxMealsPerDay,
                                   const unsigned int& p_nbOfCycles) :
    m_sageCount(p_nbOfSages),
    m_maxMealsPerDay(p_maxMealsPerDay),
    m_nbOfCycles(p_nbOfCycles)
{
    for (unsigned int i = 0; i < p_nbOfSages; ++i)
    {
        m_sages.emplace_back();
        m_threads.emplace_back();
        m_baguetteMutexes.emplace_back();
    }
}

void Managers::SageManager::Init()
{
    for (unsigned int i = 0; i < m_sageCount; ++i)
    {
        m_threads[i] = std::thread(&Sage::Main, &m_sages[i],
                                   std::ref(m_baguetteMutexes[i]),
                                   std::ref(m_baguetteMutexes[(i + 1)
                                                % m_sageCount]));
    }

    UpdateCycle();

    for (auto& thread : m_threads)
        thread.join();
}

void Managers::SageManager::DisplaySageStates(const Sage& p_sage)
{
    std::cout << p_sage.GetState() << '|';
}

void Managers::SageManager::UpdateCycle()
{
    unsigned int daysPassed{1};
    int          isDayOver{0};

    while (daysPassed <= m_nbOfCycles)
    {
        // There is no way but this one to clear completely the console in C++
        system("cls");

        std::cout << "Day " << daysPassed << '\n';
        for (auto& sage : m_sages)
        {
            DisplaySageStates(sage);

            if (sage.GetEatingRecord() >= m_maxMealsPerDay
                    ? ++isDayOver
                    : --isDayOver)
            {
                if (isDayOver < 0)
                    isDayOver = 0;

                else if (isDayOver == static_cast<int>(m_sageCount))
                {
                    daysPassed++;
                    for (auto& sages : m_sages)
                        sages.SetEatingRecord(0);
                }
            }
        }

        if (isDayOver < static_cast<int>(m_sageCount))
            isDayOver = 0;

        std::cout << '\r';

        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
    for (auto& sage : m_sages)
    {
        sage.SetIsCycleOver(true);
    }
    
    // End cycle message
    std::cout << "Cycle is Over. " << daysPassed - 1 <<
            " days have passed since start. Every Sage has eaten "
            << m_maxMealsPerDay << " times a day.";
}
