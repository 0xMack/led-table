#include "tableout.h"
#include "ledSelector.h"

int main()
{
    tableout output;//creates object for tableout class
    ledSelector choice;
    output.setDefaultShift();
    choice.mainMenu();
    return 0;
}
