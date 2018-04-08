# CMakeLists.txt from SILENT HILL 3 Redux by Palm Studios
# Copyright 2016-2018 Alexander Hirsch and Jesse Buhagiar

find_package(GLEW REQUIRED)
find_package(GLU REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

include_directories("../include")
include_directories(SYSTEM "${GLEW_INCLUDE_DIRS}")
include_directories(SYSTEM "${GLUT_INCLUDE_DIR}")
include_directories(SYSTEM "${OPENGL_INCLUDE_DIR}")

add_executable("${CMAKE_PROJECT_NAME}"

    "euclidean1/main.c"

    "euclidean1/system/window.c"
    "euclidean1/system/engine.c"

    "euclidean1/math/vec2.c"

    "euclidean1/object/waves.c"
    "euclidean1/object/cannon.c"
    "euclidean1/object/boat.c"

)

target_link_libraries("${CMAKE_PROJECT_NAME}"

    PRIVATE "${OPENGL_LIBRARIES}"
    PRIVATE "${GLU_LIBRARIES}"
    PRIVATE "${GLUT_LIBRARIES}"
    PRIVATE "m"
)
