add_compile_options(-std=c++11)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

# openrtm has deprecated coding. This causes too many warnings.
#   warning: dynamic exception specifications are deprecated in C++11
add_definitions(-Wno-deprecated)

find_package(catkin REQUIRED COMPONENTS
  rtmbuild
  imu_filter_madgwick
  )
find_package(PkgConfig REQUIRED)
pkg_check_modules(EIGEN eigen3>=3.2.7)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${EIGEN_INCLUDE_DIRS}
  )

rtmbuild_add_library(MadgwickFilter SHARED
  MadgwickFilter.cpp
  MadgwickFilterService_impl.cpp
  )
target_link_libraries(MadgwickFilter
  ${catkin_LIBRARIES}
  ${EIGEN_LIBRARIES}
  )
set_target_properties(MadgwickFilter PROPERTIES PREFIX "")
add_dependencies(MadgwickFilter RTMBUILD_${PROJECT_NAME}_genrpc) # wait for rtmbuild_genidl

rtmbuild_add_executable(MadgwickFilterComp MadgwickFilterComp.cpp)
target_link_libraries(MadgwickFilterComp MadgwickFilter)
