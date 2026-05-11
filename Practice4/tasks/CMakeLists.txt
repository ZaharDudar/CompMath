file(GLOB_RECURSE Tasks *.cpp)

include(FetchContent)

FetchContent_Declare(
        eigen
        GIT_REPOSITORY "https://gitlab.com/libeigen/eigen.git"
        GIT_TAG 5.0.0
)

FetchContent_MakeAvailable(eigen)


FetchContent_Declare(
        LinearSystemSolver
        GIT_REPOSITORY "https://github.com/ZaharDudar/LinearSystemSolver.git"
        GIT_TAG main
)

FetchContent_MakeAvailable(LinearSystemSolver)

foreach(Task IN LISTS Tasks)
    get_filename_component(FILE_NAME ${Task} NAME_WLE)
    add_executable(${FILE_NAME} ${Task})
    target_compile_definitions(${FILE_NAME} PUBLIC OUTPUT_DIR="${CMAKE_SOURCE_DIR}/python/output/")
endforeach()

target_link_libraries(filtering PRIVATE LinearSystemSolver)
target_link_libraries(heat PRIVATE LinearSystemSolver)
target_link_libraries(HLL PRIVATE eigen)
target_link_libraries(HLLc PRIVATE eigen)

