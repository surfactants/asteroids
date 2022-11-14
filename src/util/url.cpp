#include <util/url.hpp>

#include <windows.h>
#include <shellapi.h>

void launchURL(std::string target)
{
    ShellExecute(0, 0, target.c_str(), 0, 0, SW_SHOW);
}
