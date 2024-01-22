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
aux_source_directory(IOTServer/models MODEL_SRC)

aux_source_directory(IOTServer/mqtt MQTT_SRC)

aux_source_directory(IOTServer/http/controllers HTTP_SRC)
aux_source_directory(IOTServer/http/filters HTTP_SRC)

aux_source_directory(IOTServer/api/cq API_SRC)
aux_source_directory(IOTServer/api API_SRC)

aux_source_directory(IOTServer/cq CQ_SRC)

aux_source_directory(IOTServer/common COMMON_SRC)

add_executable(
        ${PROJECT_NAME}
        IOTServer/main.cc
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
        ${CMAKE_CURRENT_SOURCE_DIR}/IOTServer/models
        ${CMAKE_CURRENT_SOURCE_DIR}/IOTServer/http/controllers
        ${CMAKE_CURRENT_SOURCE_DIR}/IOTServer/http/filters
        ${CMAKE_CURRENT_SOURCE_DIR}/IOTServer/api/cq
        ${CMAKE_CURRENT_SOURCE_DIR}/IOTServer/api
        ${CMAKE_CURRENT_SOURCE_DIR}/IOTServer/common
        ${CMAKE_CURRENT_SOURCE_DIR}/IOTServer/mqtt
        ${CMAKE_CURRENT_SOURCE_DIR}/IOTServer/cq
)


target_sources(${PROJECT_NAME}
        PRIVATE
        ${SRC_DIR}
        ${API_SRC}
        ${HTTP_SRC}
        ${MQTT_SRC}
        ${MODEL_SRC}
        ${COMMON_SRC}
        ${CQ_SRC}
)


add_subdirectory(test)