#include <fstream>
#include <nlohmann/json.hpp>
#include "include/material.h"

using namespace Odyssey;

Material* Material::load(const std::string &json_file){
    std::ifstream fstream(json_file);
    nlohmann::json json = nlohmann::json::parse(fstream);
    Material* material = new Material();
    return nullptr;
}
