#include <Managers/SageManager.h>
#include <iostream>

using namespace Entity;

Managers::SageManager::SageManager(const unsigned int& p_nbOfSages,
                                   const unsigned int& p_maxMealsPerDay,
                                   const unsigned int& p_nbOfCycles) :
    m_sageCountRef(p_nbOfSages),
    m_maxMealsPerDay(p_maxMealsPerDay),
    m_nbOfCycles(p_nbOfCycles)
{
    m_sages           = new Entity::Sage[p_nbOfSages];
    m_threads         = new std::thread[p_nbOfSages];
    m_baguetteMutexes = new std::mutex[p_nbOfSages];
}

Managers::SageManager::~SageManager()
{
    delete[] m_sages;
    delete[] m_threads;
    delete[] m_baguetteMutexes;
}

void Managers::SageManager::Init()
{
    for (unsigned int i = 0; i < m_sageCountRef; ++i)
    {
        m_threads[i] = std::thread(&Sage::Main, &m_sages[i],
                                   std::ref(m_baguetteMutexes[i]),
                                   std::ref(m_baguetteMutexes[(i + 1) %
                                                m_sageCountRef]));
    }

    UpdateCycle();

    for (unsigned int i = 0; i < m_sageCountRef; ++i)
        m_threads[i].join();
}

void Managers::SageManager::DisplaySageStates(const Sage p_sage)
{
    std::cout << p_sage.GetState() << '|';
}

void Managers::SageManager::UpdateCycle()
{
    unsigned int       daysPassed{ 1 };
    int                isDayOver{ 0 };

    while (daysPassed <= m_nbOfCycles)
    {
        system("cls");

        std::cout << "Day " << daysPassed << '\n';
        for (unsigned int i = 0; i < m_sages->GetSageCount(); i++)
        {
            DisplaySageStates(m_sages[i]);

            if (m_sages[i].GetEatingRecord() >= m_maxMealsPerDay
                ? ++isDayOver
                : --isDayOver)
            {
                if (isDayOver < 0)
                    isDayOver = 0;

                else if (isDayOver == static_cast<int>(m_sages->GetSageCount()))
                {
                    daysPassed++;
                    for (unsigned int n = 0; n < m_sages->GetSageCount(); n++)
                        m_sages[n].SetEatingRecord(0);
                }
            }
        }

        if (isDayOver < static_cast<int>(m_sages->GetSageCount()))
            isDayOver = 0;

        std::cout << '\r';

        std::this_thread::sleep_for(std::chrono::seconds{ 1 });
    }
    for (unsigned int i = 0; i < m_sages->GetSageCount(); i++)
    {
        m_sages[i].SetIsCycleOver(true);
    }
    std::cout << "Cycle is Over. " << daysPassed - 1 <<
        " days have passed since start. Every Sage has eaten "
        << m_maxMealsPerDay << " times a day.";
}
