
# opencv
find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

## MM
include_directories(${ModelM_DIR}/include)
SET(ModelM_libs ${ModelM_DIR}/lib/libModelM_shared.so)

## lib
file(GLOB_RECURSE SRC_LIB_OCR
    src/*.h
    src/*.hpp
    src/*.cpp
    src/*.c
    )
add_library(OcrInfer
    ${SRC_LIB_OCR}
    )

target_link_libraries(OcrInfer PUBLIC
    ${FastDeploy_LIBS}
    ${ModelM_libs}
    ${OpenCV_LIBS}
    )

## test
file(GLOB_RECURSE SRC_OCR_TEST
    main/*.h
    main/*.hpp
    main/*.cpp
    )
add_executable(OcrTest
    ${SRC_OCR_TEST}
    )
target_link_libraries(OcrTest PUBLIC OcrInfer)

## testWraper
file(GLOB_RECURSE SRC_TEST_WRAPPER
    mainWrap/*.h
    mainWrap/*.hpp
    mainWrap/*.cpp
    )
add_executable(OcrTestWrap
    ${SRC_TEST_WRAPPER}
    )
