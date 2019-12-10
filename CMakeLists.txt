cmake_minimum_required(VERSION 3.10)

project(bump)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 14)

# library target
set(LIB_NAME ${PROJECT_NAME})
add_library(${LIB_NAME}
    src/bump.cpp
)
target_include_directories(${LIB_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# install library
install(TARGETS ${LIB_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/bump
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/bump
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/bump
)
# install header files
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/bump
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
# generate cmake config file to export this project's cmake targets
set(EXPORT_CONFIG_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake)
set(EXPORT_CONFIG_INSTALL_DIR ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME})
CONFIGURE_PACKAGE_CONFIG_FILE(
    ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${EXPORT_CONFIG_FILE}
    INSTALL_DESTINATION ${EXPORT_CONFIG_INSTALL_DIR}
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
install(EXPORT ${PROJECT_NAME}Targets
    DESTINATION ${EXPORT_CONFIG_INSTALL_DIR}
)
install(FILES ${EXPORT_CONFIG_FILE}
    DESTINATION ${EXPORT_CONFIG_INSTALL_DIR}
)
