
message(STATUS "BUILDING COMPLETE PROJECT")

# Build module first
add_subdirectory(geohash)

# Then build and link the app, which uses module
add_subdirectory(app)


