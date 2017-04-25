cmake_minimum_required(VERSION 2.8)

# Application source
set(APPLICATION_SOURCE

    fluid.cpp

    # Collision objects
    collision/sphere.cpp
    collision/plane.cpp

    # Application
    simulator.cpp
    main.cpp

    # Miscellaneous
    # png.cpp
    misc/sphere_drawing.cpp

    # Camera
    camera.cpp
)

#-------------------------------------------------------------------------------
# Embed resources
#-------------------------------------------------------------------------------

# embed_resources(FLUIDSIMULATOR_SHADERS
#   shaders/vert.glsl
#   shaders/normalFrag.glsl
#   shaders/wireframeFrag.glsl
# )

#-------------------------------------------------------------------------------
# Set definitions
#-------------------------------------------------------------------------------
add_definitions(${NANOGUI_EXTRA_DEFS})

#-------------------------------------------------------------------------------
# Set include directories
#-------------------------------------------------------------------------------
include_directories(
  ${CGL_INCLUDE_DIRS}
  ${FREETYPE_INCLUDE_DIRS}
  ${NANOGUI_EXTRA_INCS}
)

#-------------------------------------------------------------------------------
# Set link directories
#-------------------------------------------------------------------------------
link_directories(
  ${CGL_LIBRARY_DIRS}
  ${FREETYPE_LIBRARY_DIRS}
)

#-------------------------------------------------------------------------------
# Add executable
#-------------------------------------------------------------------------------
add_executable(fluidsimulator ${APPLICATION_SOURCE})

target_link_libraries(fluidsimulator
    CGL ${CGL_LIBRARIES}
    nanogui ${NANOGUI_EXTRA_LIBS}
    ${FREETYPE_LIBRARIES}
    ${CMAKE_THREADS_INIT}
)

#-------------------------------------------------------------------------------
# Platform-specific configurations for target
#-------------------------------------------------------------------------------
if(APPLE)
  set_property( TARGET fluidsimulator APPEND_STRING PROPERTY COMPILE_FLAGS
                "-Wno-deprecated-declarations -Wno-c++11-extensions")
endif(APPLE)

# Put executable in build directory root
set(EXECUTABLE_OUTPUT_PATH ..)

# Install to project root
install(TARGETS fluidsimulator DESTINATION ${FluidSimulator_SOURCE_DIR})
