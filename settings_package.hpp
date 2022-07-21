#pragma once

#include <map>
#include "volume_type.hpp"

struct Settings_Package{
    std::map<Volume_Type, float> volume;
};
