add_library(chiselModule INTERFACE)
target_link_libraries(chiselModule INTERFACE
    chiselProject
)

add_library(chiselProject STATIC ChiselProject.cpp)

target_include_directories(chiselProject PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

target_link_libraries(chiselProject PUBLIC
    tempProjectDir
)
add_folders(ChiselModule)