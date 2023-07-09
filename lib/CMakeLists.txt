include(ExternalProject)

ExternalProject_Add(
    freetype
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/freetype/
    PATCH_COMMAND patch -p1 < ${CMAKE_CURRENT_SOURCE_DIR}/freetype.patch
    CMAKE_ARGS
        -DWASI_SDK_PREFIX=${WASI_SDK_DIR}
        -DCMAKE_TOOLCHAIN_FILE=${WASI_SDK_DIR}/share/cmake/wasi-sdk-pthread.cmake
        -DCMAKE_SYSROOT=${WASI_SDK_DIR}/share/wasi-sysroot
        -DBUILD_SHARED_LIBS=OFF
        -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
        -DLIB_DIR=${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(libfreetype STATIC IMPORTED GLOBAL)
set_property(TARGET libfreetype PROPERTY IMPORTED_LOCATION ${DEPS_INSTALL_DIR}/lib/libfreetype.a)
set_property(TARGET libfreetype PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/freetype/include)
add_dependencies(libfreetype freetype)