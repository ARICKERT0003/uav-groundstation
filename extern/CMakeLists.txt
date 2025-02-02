cmake_minimum_required( VERSION 3.12 )
project( uav-groundstation
  LANGUAGES CXX
  VERSION   0.0.0
  DESCRIPTION "Ground Station for quad UAV"
)

#############################
# Recurse into Subdirectories
#############################

# Mavlink
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/mavlink )

#############################
# Collect Files and Dirs
#############################

set( UAVGS_EXTERN_INC_DIRS
  ${UAVGS_MAVLINK_INC_DIRS}
  PARENT_SCOPE
)

set( UAVGS_EXTERN_COMPILE_FLAGS
  ${UAVGS_MAVLINK_COMPILE_FLAGS}
  PARENT_SCOPE
)
