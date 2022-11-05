#pragma once

#include <audio/volume_type.hpp>
#include <map>

struct Settings_Package {
    std::map<Volume_Type, float> volume;
};
