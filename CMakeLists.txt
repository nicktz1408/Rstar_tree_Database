cmake_minimum_required(VERSION 3.17)
project(Rstar_tree_Database)

set(CMAKE_CXX_STANDARD 14)

include_directories(rapidxml-1.13)

add_executable(Rstar_tree_Database
        rapidxml-1.13/rapidxml.hpp
        rapidxml-1.13/rapidxml_iterators.hpp
        rapidxml-1.13/rapidxml_print.hpp
        rapidxml-1.13/rapidxml_utils.hpp
        Database_Technology_Project.cpp
        R_tree_structure.cpp)
