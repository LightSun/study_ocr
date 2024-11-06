
#
include_directories(${ModelM_DIR}/include)
#
file(GLOB_RECURSE SRC_PYBIND
    src/*.h
    src/*.hpp
    src/*.cpp
    src/*.c
    src/*.cc
    )

add_library(PyOcrInfer MODULE
    ${SRC_PYBIND}
    )
target_include_directories(PyOcrInfer PUBLIC ${PY_BIND11_DIR}/include)
set_target_properties(PyOcrInfer
  PROPERTIES
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
  )
#target_link_directories(PyOcrInfer PUBLIC xxx)
target_link_libraries(PyOcrInfer PUBLIC OcrInfer
    pybind11::module
    )
