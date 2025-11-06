#pragma once

#include <memory>
#include <string>
#include <vector>

#include "core/hittable.hpp"

std::vector<std::shared_ptr<Hittable>> load_scene_from_json_file(const std::string& filename);
