# CMakeList.txt : CMake project for GraviSim, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (GraviSim  
	"main.cpp"
 "MainWindow.cpp"
     "Screen.hpp" "Screen.cpp" "Planet.hpp" "Planet.cpp" "PlanetConfig.cpp" )

target_link_libraries(GraviSim
	Qt5::Widgets
    Qt5::Core
)

add_custom_command(TARGET GraviSim POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:GraviSim>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:GraviSim>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:GraviSim>
    )