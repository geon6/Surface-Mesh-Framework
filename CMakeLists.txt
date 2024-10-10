cmake_minimum_required(VERSION 3.20)

project(SurfaceMeshFramework)

add_definitions(/D_USE_MATH_DEFINES)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QRC_SOURCE_FILES src/surfacemeshprocessing.qrc)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)
find_package(Eigen3 CONFIG REQUIRED)
find_package(openmesh REQUIRED)
find_package(spdlog CONFIG REQUIRED)

qt6_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

file(GLOB_RECURSE headers CONFIGURE_DEPENDS include/**)
file (GLOB GUI_FILE
    src/main.cpp
    src/MeshViewer/MainViewerWidget.cpp
    src/MeshParamWidget.cpp
    src/surfacemeshprocessing.cpp
)
file (GLOB MeshViewer_FILE
    src/MeshViewer/InteractiveViewerWidget.cpp
    src/MeshDefinition.cpp
    src/MeshViewer/MeshViewerWidget.cpp
    src/MeshViewer/QGLViewerWidget.cpp
)

qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    ${GUI_FILE}
    ${MeshViewer_FILE}
    ${QRC_FILES}
    ${headers} # 一定要把头文件放到这里, 要不然auto moc扫描不到头文件里的 Q_OBJECT, 编译就会失败
)

target_compile_options(${PROJECT_NAME} 
	PRIVATE 
	$<$<CXX_COMPILER_ID:MSVC>:/bigobj>
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Widgets Qt6::Core Qt6::Gui Qt6::OpenGL Qt6::OpenGLWidgets
    Eigen3::Eigen
    spdlog::spdlog spdlog::spdlog_header_only
    ${OPENMESH_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${OPENMESH_INCLUDE_DIRS}
    include
)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(${PROJECT_NAME} PRIVATE
        opengl32
        glu32
    )
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${GLUT_LIBRARY} 
        ${OPENGL_LIBRARY}
    )
endif()
