cmake_minimum_required(VERSION 2.8.12)
project(NANOGL)

set(NANOGL_LIB nanogl)

file(GLOB NANOGL_SRC "*.cpp")

add_library(${NANOGL_LIB} STATIC ${NANOGL_SRC})

target_compile_definitions(${NANOGL_LIB} PRIVATE __MULTITEXTURE_SUPPORT__ NANOGL_MANGLE_PREPEND)

target_include_directories(
	${NANOGL_LIB} PRIVATE
	"GL"
)