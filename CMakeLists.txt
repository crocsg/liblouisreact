cmake_minimum_required(VERSION 3.10)

set (PROJECT_NAME "liblouisreact")

set(CMAKE_SYSTEM_NAME Emscripten)

project(${PROJECT_NAME})

add_definitions(-DEMSCRIPTEN_SUPPORT)
add_definitions(-DCMAKE_TOOLCHAIN_FILE=$ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
add_definitions(-DCMAKE_CROSSCOMPILING_EMULATOR=$ENV{EMSDK_NODE})
add_definitions(-DLOU_STREAM_OVERRIDE)


file(GLOB_RECURSE ENCODED 
   generated/*.c 
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
    
    proxy/emfile.c
    proxy/emfile.h
    proxy/test.c
    proxy/proxy.c
    proxy/lou_file_override.h
    database/loudatabase.c
    
    ${ENCODED}
 )

target_include_directories(${PROJECT_NAME}  PRIVATE
   generated/
   proxy/   
   database/
   liblouis/liblouis/
) 
  



set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Oz --no-entry  \
    --pre-js \
    ${CMAKE_SOURCE_DIR}/addons/locateFile.js \
    -s TOTAL_MEMORY=512mb \
    -s ENVIRONMENT='web' \
    -s STACK_SIZE=5242880 \
    -s EXPORT_NAME='createModule' \
    -s USE_ES6_IMPORT_META=0 \
    -s EXPORTED_FUNCTIONS='[\"_malloc\", \"_free\", \"_test_file\", \"_test_lasterror\", \"_test_translate_fr\", \"_test_add\"]' \
    -s EXPORTED_RUNTIME_METHODS='[\"ccall\", \"cwrap\", \"stringToUTF32\", \"UTF32ToString\", \"lengthBytesUTF32\", \"AsciiToString\"]'  ")
