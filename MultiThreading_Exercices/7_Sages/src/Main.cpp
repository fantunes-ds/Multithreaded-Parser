#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include <Entity/Sage.h>

using namespace Entity;

void DisplaySages(Sage* sages)
{
    unsigned int daysPassed{1};
    int          isDayOver{0};
    unsigned int          maxEatingTimesPDay{3};
    unsigned int          nbOfCycles{7};
    while (daysPassed <= nbOfCycles)
    {
        system("cls");

        std::cout << "Day " << daysPassed << '\n';
        for (unsigned int i = 0; i < sages->GetSageCount(); i++)
        {
            std::cout << sages[i].GetState() << '|';

            if (sages[i].GetEatingRecord() >= maxEatingTimesPDay ? ++isDayOver : --isDayOver)
            {
                if (isDayOver < 0)
                    isDayOver = 0;

                else if (isDayOver == sages->GetSageCount())
                {
                    daysPassed++;
                    for (unsigned int n = 0; n < sages->GetSageCount(); n++)
                        sages[n].SetEatingRecord(0);
                }
            }
        }

        if (isDayOver < static_cast<int>(sages->GetSageCount()))
            isDayOver = 0;

        std::cout << '\r';

        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
    for (unsigned int i = 0; i < sages->GetSageCount(); i++)
    {
        sages[i].SetIsCycleOver(true);
    }
        std::cout << "Cycle is Over " << daysPassed - 1 <<
                     " days have passed since start. Every Sage has eaten "
                    << maxEatingTimesPDay << " times a day.";
}

int main(void)
{
    Sage        sages[7];
    std::thread threads[7];
    std::mutex  baguetteMutex[7];

    const unsigned int sageCountRef = sages->GetSageCount();

    for (unsigned int i = 0; i < sageCountRef; ++i)
    {
        //t=std::move()
        threads[i] = std::thread(&Sage::Main, &sages[i], std::ref(baguetteMutex[i]),
                                 std::ref(baguetteMutex[(i + 1) % sageCountRef]));
        std::cout << (i + 1) % sageCountRef << '\n';
    }

    DisplaySages(sages);

    for (auto& thread : threads)
        thread.join();

    return 0;
}
