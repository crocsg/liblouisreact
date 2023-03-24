cmake_minimum_required(VERSION 3.10)
set (PROJECT_NAME "simple")

set(CMAKE_SYSTEM_NAME Emscripten)

project(${PROJECT_NAME})

add_definitions(-DEMSCRIPTEM_SUPPORT)
add_definitions(-DEMSCRIPTEM_REACT_SUPPORT)
add_definitions(-DCMAKE_TOOLCHAIN_FILE=$ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
add_definitions(-DCMAKE_CROSSCOMPILING_EMULATOR=$ENV{EMSDK_NODE})

file(GLOB_RECURSE ENCODED 
   encoded/*.c 
)

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
    proxy/emfile.c
    proxy/emfile.h
    proxy/test.c
    ${ENCODED}
 )

target_include_directories(${PROJECT_NAME}  PRIVATE
   encoded/
   proxy/   
   liblouis/liblouis/
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
    -s TOTAL_MEMORY=128mb \
    -s ENVIRONMENT='web' \
    -s EXPORT_NAME='createModule' \
    -s USE_ES6_IMPORT_META=0 \
    -s EXPORTED_FUNCTIONS='[\"_test_add\", \"_set_str\",\"_get_str\", \"_malloc\", \"_free\", \"_test_file\", \"_test_lasterror\", \"_test_translate_fr\"]' \
    -s EXPORTED_RUNTIME_METHODS='[\"ccall\", \"cwrap\", \"stringToUTF32\", \"UTF32ToString\", \"lengthBytesUTF32\", \"AsciiToString\"]'  ")
