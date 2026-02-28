file(GLOB_RECURSE Tasks *.cpp)

foreach(Task IN LISTS Tasks)
    get_filename_component(FILE_NAME ${Task} NAME_WLE)
    add_executable(${FILE_NAME} ${Task})
    target_compile_definitions(${FILE_NAME} PUBLIC OUTPUT_DIR="${CMAKE_SOURCE_DIR}/python/output/")
endforeach()


