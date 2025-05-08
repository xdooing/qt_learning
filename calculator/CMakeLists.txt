cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)


# 使用cmake编译qt项目的时候最好是加上
# AUTOMOC负责自动生成Qt的元对象代码（moc），处理信号槽等特性。如果用户的项目中有Q_OBJECT宏的类，这个设置会自动调用moc工具，不需要手动添加命令。
# AUTORCC用于自动处理资源文件（.qrc），将资源编译成C++代码，这样在代码中可以通过资源路径访问。启用后，CMake会自动处理添加到项目中的.qrc文件。
# AUTOUIC处理用户界面编译，自动将.ui文件（Qt Designer创建的界面文件）生成对应的头文件，这样可以直接在代码中包含和使用这些UI类。
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(calculator)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
file(GLOB sources *.cpp)
add_executable(calculator ${sources})
target_link_libraries(calculator PRIVATE Qt5::Core Qt5::Widgets)

