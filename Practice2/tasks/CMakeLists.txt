file(GLOB_RECURSE Tasks *.cpp)

include(FetchContent)
FetchContent_Declare(
        LinearSystemSolver
        GIT_REPOSITORY https://github.com/ZaharDudar/LinearSystemSolver.git
        GIT_TAG main
)
FetchContent_MakeAvailable(LinearSystemSolver)

foreach(Task IN LISTS Tasks)
    get_filename_component(FILE_NAME ${Task} NAME_WLE)
    add_executable(${FILE_NAME} ${Task})
    target_compile_definitions(${FILE_NAME} PUBLIC OUTPUT_DIR="${CMAKE_SOURCE_DIR}/python/output/")
    target_link_libraries(${FILE_NAME} LinearSystemSolver)
endforeach()

target_compile_options(X.9.3 PUBLIC -O3)
target_compile_options(T3 PUBLIC -O3)
target_compile_options(T4Linearize PUBLIC -O3)
target_compile_options(T4Shooting PUBLIC -O3)
target_compile_options(T5 PUBLIC -O3)

