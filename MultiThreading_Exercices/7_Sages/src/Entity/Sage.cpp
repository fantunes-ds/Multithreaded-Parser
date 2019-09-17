#include <Entity/Sage.h>

#include <thread>
#include <iostream>

int sageCount = 0;

Entity::Sage::Sage() : m_id(sageCount++)
{
    std::cout << "A new sage has joined the table. Welcome sage " << m_id << '\n';
}

void Entity::Sage::Main()
{
    std::cout << "Sage has lived well\n";
}