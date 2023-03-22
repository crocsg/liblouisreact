cmake_minimum_required(VERSION 3.10)
set (PROJECT_NAME "simple")

set(CMAKE_SYSTEM_NAME Emscripten)

project(${PROJECT_NAME})

add_definitions(-DEMSCRIPTEM_SUPPORT)
add_definitions(-DCMAKE_TOOLCHAIN_FILE=/home/dev/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
add_definitions(-DCMAKE_CROSSCOMPILING_EMULATOR=/home/dev/emsdk/node/14.18.2_64bit/bin/node)

#file(GLOB_RECURSE FILES 
#  liblouis/liblouis/*.c 
#  liblouis/liblouis/*.cpp 
#  liblouis/liblouis/*.h
#)



set(CMAKE_EXECUTABLE_SUFFIX ".mjs")
add_executable(${PROJECT_NAME}
  
    liblouis/liblouis/compileTranslationTable.c		
    liblouis/liblouis/lou_translateString.c			
    liblouis/liblouis/lou_backTranslateString.c		
    liblouis/liblouis/commonTranslationFunctions.c		
    liblouis/liblouis/metadata.c 				
    liblouis/liblouis/pattern.c				
    liblouis/liblouis/logging.c				
    liblouis/liblouis/utils.c				
    liblouis/liblouis/maketable.c
    addons/simple.c
 )
  
#set some Emscripten options
#if(FALSE) # fake a block comment
#--no-entry simple.c -o simple.mjs   `
#    --pre-js ../src/locateFile.js   `
#    -s ENVIRONMENT='web'   `
#    -s EXPORT_NAME='createModule'   `
#    -s USE_ES6_IMPORT_META=0   `
#    -s EXPORTED_FUNCTIONS='["_test_add", "_set_str","_get_str", "_malloc", "_free"]'   `
#    -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap", "stringToUTF32", "UTF32ToString", "lengthBytesUTF32"]'  
#endif()


set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--no-entry  \
    --pre-js \
    ../addons/locateFile.js \
    -s ENVIRONMENT='web' \
    -s EXPORT_NAME='createModule' \
    -s USE_ES6_IMPORT_META=0 \
    -s EXPORTED_FUNCTIONS='[\"_test_add\", \"_set_str\",\"_get_str\", \"_malloc\", \"_free\"]' \
    -s EXPORTED_RUNTIME_METHODS='[\"ccall\", \"cwrap\", \"stringToUTF32\", \"UTF32ToString\", \"lengthBytesUTF32\"]'  ")
