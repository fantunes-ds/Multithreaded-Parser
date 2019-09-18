#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include <Entity/Sage.h>

using namespace Entity;


void DisplaySages(Sage* sages)
{
    while (true)
    {
        for (unsigned int i = 0; i < sages->GetSageCount(); i++)
        {
            std::cout << sages[i].GetState() << '/';
        }
        std::cout << '\r';

        std::this_thread::sleep_for(std::chrono::milliseconds{ 50});
    }
}

int main(void)
{
    Sage sages[7];
    std::thread threads[7];
    std::mutex baguettes[7];
    for (unsigned int i = 0; i < 7; ++i)
    {
        //t=std::move()
        threads[i] = std::thread(&Sage::Main, &sages[i]);
    }

    DisplaySages(sages);

    for (auto& thread : threads)
        thread.join();

    return 0;
}