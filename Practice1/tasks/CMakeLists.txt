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
endforeach()
target_link_libraries(VI.9.32 LinearSystemSolver)
target_link_libraries(T1 LinearSystemSolver)
