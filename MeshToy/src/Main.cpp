#include <format>
#include <iostream>

#include "Demo/BaseApp/BaseApp.h"

#include "yaml-cpp/yaml.h"

int main(int argc, char* argv[])
{
    BaseApp App;
    
    App.Start();
    App.Run();
    
    return 0;
}
