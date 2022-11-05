#include <shellapi.h>
#include <util/url.hpp>
#include <windows.h>

void launchURL(std::string target)
{
    ShellExecute(0, 0, target.c_str(), 0, 0, SW_SHOW);
}
