# 最低支持版本
cmake_minimum_required(VERSION 3.0)
# 设置项目名
project(OpenGLPractice)

# 设置可执行文件生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# set(CMAKE_CXX_STANDARD 17)

# 设置源文件
# set(SOURCES 
#     src/main.cpp
#     src/Temp.cpp
# )

set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
link_directories(${LIB_DIR})

# 查找src下所有源文件并存储在 SOURCE_DIR
aux_source_directory(src SOURCE_DIR)
# 指定生成目标
add_executable(${PROJECT_NAME} ${SOURCE_DIR})
# 链接头文件
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_library(assimp STATIC IMPORTED)
set_target_properties(assimp PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/libassimp.a)

# add_library(IrrXML STATIC IMPORTED)
# set_target_properties(IrrXML PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/libIrrXML.a)

# 链接三方库
target_link_libraries(${PROJECT_NAME} 
    glad
    glfw3
    opengl32
    assimp
    zlibstatic
    IrrXML
    ${LIB_DIR}/libopencv_calib3d3412.a
    ${LIB_DIR}/libopencv_core3412.a
    ${LIB_DIR}/libopencv_dnn3412.a
    ${LIB_DIR}/libopencv_features2d3412.a
    ${LIB_DIR}/libopencv_flann3412.a
    ${LIB_DIR}/libopencv_highgui3412.a
    ${LIB_DIR}/libopencv_imgcodecs3412.a
    ${LIB_DIR}/libopencv_imgproc3412.a
    ${LIB_DIR}/libopencv_ml3412.a
    ${LIB_DIR}/libopencv_objdetect3412.a
    ${LIB_DIR}/libopencv_photo3412.a
    ${LIB_DIR}/libopencv_shape3412.a
    ${LIB_DIR}/libopencv_stitching3412.a
    ${LIB_DIR}/libopencv_superres3412.a
    ${LIB_DIR}/libopencv_ts3412.a
    ${LIB_DIR}/libopencv_video3412.a
    ${LIB_DIR}/libopencv_videoio3412.a
    ${LIB_DIR}/libopencv_videostab3412.a
    ${LIB_DIR}/liblibtiff.a
    ${LIB_DIR}/liblibjpeg-turbo.a
    ${LIB_DIR}/liblibjasper.a
    ${LIB_DIR}/liblibwebp.a
    ${LIB_DIR}/liblibprotobuf.a
    ${LIB_DIR}/liblibpng.a
    ${LIB_DIR}/libIlmImf.a
    ${LIB_DIR}/libquirc.a
)