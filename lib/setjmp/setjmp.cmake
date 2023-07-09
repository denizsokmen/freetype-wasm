project(setjmp C ASM)

set(MAIN_TARGET_NAME "setjmp")
add_library(${MAIN_TARGET_NAME} STATIC ${CMAKE_CURRENT_LIST_DIR}/setjmp.c ${CMAKE_CURRENT_LIST_DIR}/setjmp_core.S)
target_include_directories(${MAIN_TARGET_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/inc>  
    $<INSTALL_INTERFACE:setjmp/inc>)
