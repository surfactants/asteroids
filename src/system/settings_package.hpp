#pragma once

#include <map>
#include <audio/volume_type.hpp>

struct Settings_Package{
    std::map<Volume_Type, float> volume;
};
