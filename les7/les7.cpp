#include "serializer.h"

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    try
    {
        std::string fileName{ "group.txt" };
        Serializer sr{ fileName };
        sr.CreateGroup();
        sr.ShowInfo();
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    
    return 0;
}

