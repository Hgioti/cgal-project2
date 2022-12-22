cmake_minimum_required(VERSION 3.1...3.23)
project(to_polygon)

# CGAL and its components
find_package( CGAL QUIET COMPONENTS  )

if ( NOT CGAL_FOUND )
    message(STATUS "This project requires the CGAL library, and will not be compiled.")
    return()
endif()

# Boost and its components
find_package( Boost REQUIRED )

if ( NOT Boost_FOUND )
    message(STATUS "This project requires the Boost library, and will not be compiled.")
    return()
endif()

# include for local directory
add_subdirectory(includes)
list(APPEND EXTRA_LIBS utils)
# include for local package

add_executable(to_polygon main.cpp includes/Incremental.cpp includes/Incremental.h includes/ConvexHull.cpp includes/ConvexHull.h includes/Polygon.cpp includes/Polygon.h)

add_to_cached_list( CGAL_EXECUTABLE_TARGETS to_polygon )

# Link the executable to CGAL and third-party libraries
target_link_libraries(to_polygon PRIVATE CGAL::CGAL ${EXTRA_LIBS})
