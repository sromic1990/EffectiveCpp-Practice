# Items/CMakeLists.txt

# Recursively find all main.cpp under Items/
file(GLOB_RECURSE EFFECTIVECPP_MAINS
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*/main.cpp"
)

foreach(main_src ${EFFECTIVECPP_MAINS})
    # main_src is something like:
    # D:/GitRepos/EffectiveCpp-Practice/Items/2/1_MACRO_EXORCISM_Refactor/src/1.1/main.cpp

    # Directory containing main.cpp (the exercise folder)
    get_filename_component(exercise_dir "${main_src}" DIRECTORY)

    # Path relative to Items/ (for naming & grouping)
    file(RELATIVE_PATH rel_path "${CMAKE_CURRENT_SOURCE_DIR}" "${exercise_dir}")
    # rel_path -> "2/1_MACRO_EXORCISM_Refactor/src/1.1"

    # Generate a unique target name from the relative path
    # Replace anything not [A-Za-z0-9_] with _
    string(REGEX REPLACE "[^A-Za-z0-9_]" "_" target_name "${rel_path}")
    # target_name -> "2_1_MACRO_EXORCISM_Refactor_src_1_1"

    message(STATUS "Adding executable ${target_name} from ${main_src}")

    add_executable(${target_name} "${main_src}")

    # Optional: set C++ standard if you want it per-target
    target_compile_features(${target_name} PRIVATE cxx_std_20)

    # Optional: group targets in IDE into folders matching the path
    # This makes VS/CLion show a hierarchy like Items/2/1_MACRO_EXORCISM_Refactor/src/1.1
    string(REPLACE "/" "\\" ide_folder "${rel_path}") # VS likes backslashes for folders
    set_target_properties(${target_name} PROPERTIES FOLDER "${ide_folder}")
endforeach()
