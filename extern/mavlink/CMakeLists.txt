cmake_minimum_required( VERSION 3.12 )
project( uav-groundstation
  LANGUAGES CXX
  VERSION   0.0.0
  DESCRIPTION "Ground Station for quad UAV"
)

#############################
# Collect Files and Dirs
#############################

set( UAVGS_MAVLINK_INC_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/${UAVGS_MAVLINK_DIALECT}
  PARENT_SCOPE
)

if( UAVGS_MAVLINK_SILENCE_WARNINGS )
  set( UAVGS_MAVLINK_COMPILE_FLAGS 
    " -Wno-address-of-packed-member"
    PARENT_SCOPE
  )
endif()



