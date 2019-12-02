set(EXENAME geohash)

# Sources
include_directories("${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/external/include" "${CMAKE_CURRENT_SOURCE_DIR}" ${CMAKE_CURRENT_SOURCE_DIR}/../)
file(GLOB SOURCE_FILES *.cpp)

# Add defines for exe build
# add_definitions("-DXXX=")

add_executable(${EXENAME} ${SOURCE_FILES})

set(LIBS "module")
target_link_libraries(${EXENAME} ${LIBS})

