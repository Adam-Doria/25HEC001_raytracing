#pragma once

#include <memory>
#include <string>
#include <vector>

#include "core/hittable.hpp"
#include "core/hittable_list.hpp"

void load_scene_from_json_file(const std::string& filename, hittable_list& world);
