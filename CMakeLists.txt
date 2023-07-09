
cmake_minimum_required(VERSION 3.0)
set(WASI_SDK_DIR "/opt/wasi-sdk-20.0")

set(WASI_SDK_PREFIX "${WASI_SDK_DIR}")
set(CMAKE_TOOLCHAIN_FILE "${WASI_SDK_DIR}/share/cmake/wasi-sdk-pthread.cmake")
set(CMAKE_SYSROOT "${WASI_SDK_DIR}/share/wasi-sysroot/")

project(freetypewasm)

set(DEPS_INSTALL_DIR ${CMAKE_BINARY_DIR}/libs_install)
file(MAKE_DIRECTORY ${DEPS_INSTALL_DIR}/include)

add_subdirectory(lib)

include(lib/setjmp/setjmp.cmake)
add_executable(test_ft sth.c)
target_link_libraries(test_ft libfreetype setjmp)
target_link_options(test_ft PRIVATE
  -z stack-size=10485760
  LINKER:--export=__heap_base
  LINKER:--export=__data_end
  LINKER:--export=malloc
  LINKER:--export=free
  LINKER:--export=wasm_setjmp
  LINKER:--export=wasm_longjmp
  LINKER:--shared-memory,--max-memory=20971520
  LINKER:--no-check-features
  LINKER:--allow-undefined
)
