#include <iostream>
#include "Application/Application.h"

#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    return Application::GetInstance().Run();
}
