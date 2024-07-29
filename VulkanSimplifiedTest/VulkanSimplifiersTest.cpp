import VulkanSimplifiers.Main;
import VulkanSimplifiers.Main.Data;
import VulkanSimplifiers.EventHandling;
import std;

import RunProgram;

int main()
{
    try
    {
        RunProgram();
    }
    catch (std::exception ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
