// clang-format off
#include <windows.h>
#include <shellapi.h>
// clang-format on
#include <util/url.hpp>

void launchURL(std::string target)
{
    ShellExecute(0, 0, target.c_str(), 0, 0, SW_SHOW);
}
