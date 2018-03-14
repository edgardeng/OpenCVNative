cmake_minimum_required(VERSION 3.4.1)


# 设置OpenCV-android-sdk路径

set( OpenCV_DIR src/main/jni/opencv/sdk/native/jni )
find_package(OpenCV REQUIRED)

add_library( native-lib
             SHARED
             src/main/cpp/native-lib.cpp)

find_library( # Sets the name of the path variable.
              log-lib
              log )

target_link_libraries( native-lib
                       ${log-lib}
                       ${OpenCV_LIBS}
                       jnigraphics
                       )