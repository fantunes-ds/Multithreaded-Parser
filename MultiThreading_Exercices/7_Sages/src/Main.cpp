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
        std::cout << '\n';

        std::this_thread::sleep_for(std::chrono::seconds{ 1});
    }
}

int main(void)
{
    Sage sages[7];
    std::thread threads[7];
    std::mutex baguetteMutex[7];

    unsigned int sageCountRef = sages->GetSageCount();

    for (unsigned int i = 0; i < sageCountRef; ++i)
    {
        //t=std::move()
        threads[i] = std::thread(&Sage::Main, &sages[i], std::ref(baguetteMutex[i]), std::ref(baguetteMutex[(i + 1) % sageCountRef]));
        std::cout << (i + 1) % sageCountRef << '\n';
    }

    system("cls");
    DisplaySages(sages);

    for (auto& thread : threads)
        thread.join();

    return 0;
}