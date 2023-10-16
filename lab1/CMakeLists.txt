project(lab1_project)

add_executable(lab1_project main.cpp)

# add_dependencies(lab1_project build_settings)

# target_link_libraries(lab1_project
# PRIVATE
# build_settings)

include_directories(lab1_project
 PUBLIC
  ../src/)