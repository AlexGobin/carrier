//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/carrier
//

#ifndef LOAD_CONFIG_HPP
#define LOAD_CONFIG_HPP

#include <string>
#include <fstream>
#include <unordered_map>
    
template <typename T>
using hashmap_t = std::unordered_map<uint32_t, T>;
using service_t = hashmap_t<std::pair<std::string, std::string>>;
   
service_t loadconfig(char* cfg)
{
    service_t services;
    std::ifstream fin(cfg);
    for (std::string line; std::getline(fin, line);)
    {
         if (line[0] == '#' || line.size() < 11)
             continue;
        auto pos1 = line.find_first_of(' ');
        auto pos2 = line.find_first_not_of(' ', pos1 + 1);
        auto pos3 = line.find_first_of(' ', pos2 + 1);
        auto pos4 = line.find_first_not_of(' ', pos3 + 1);
        auto service = std::stoi(line.substr(0, pos1));
        auto host = line.substr(pos2, pos3 - pos2);
        auto port = line.substr(pos4);
        services.try_emplace(service, host, port);
    }
    return services;
}

#endif
