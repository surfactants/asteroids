#include <system/shell.hpp>

#include <tests/tests.hpp>

int main()
{
    Tests tests;
    tests.run();

    Shell shell;
    shell.run();
    return 0;
}
