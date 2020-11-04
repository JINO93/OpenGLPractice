# 最低支持版本
cmake_minimum_required(VERSION 3.0)
# 设置项目名
project(OpenGLPractice)

# 设置可执行文件生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

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
# 链接三方库
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glad
    glfw3
    opengl32
)