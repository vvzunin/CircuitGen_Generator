add_library(tempProjectDir STATIC TempProjectDir.cpp)

target_include_directories(tempProjectDir PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
)

add_folders(TempProjectDir)