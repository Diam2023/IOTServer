cmake_minimum_required(VERSION 3.5)

project(IOTServer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Adding Source Code
aux_source_directory(src/controllers CTL_SRC)
aux_source_directory(src/filters FILTER_SRC)
aux_source_directory(src/plugins PLUGIN_SRC)
aux_source_directory(src/models MODEL_SRC)
aux_source_directory(src/service SERVICE_SRC)
aux_source_directory(src/cqhttp CQ_SRC)
aux_source_directory(src/api API_SRC)
aux_source_directory(src/common COMMON_SRC)

add_executable(
        ${PROJECT_NAME}
        src/main.cc
)

find_package(Qt5 COMPONENTS Core Network Mqtt REQUIRED) # Qt COMPONENTS
find_package(Drogon CONFIG REQUIRED) # Drogon CONFIG

# Drogon Qt
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Network Qt5::Mqtt Drogon::Drogon)


# Drogon View
drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
        ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/models
        ${CMAKE_CURRENT_SOURCE_DIR}/src/service
        ${CMAKE_CURRENT_SOURCE_DIR}/src/api
        ${CMAKE_CURRENT_SOURCE_DIR}/src/common
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cqhttp
)


target_sources(${PROJECT_NAME}
        PRIVATE
        ${SRC_DIR}
        ${CTL_SRC}
        ${FILTER_SRC}
        ${PLUGIN_SRC}
        ${MODEL_SRC}
        ${SERVICE_SRC}
        ${CQ_SRC}
        ${API_SRC}
        ${COMMON_SRC}
)


add_subdirectory(test)