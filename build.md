
# Activate emsdk
    /home/sgodin/contrib/emsdk/emsdk activate 3.1.45
    source /home/sgodin/contrib/emsdk/emsdk_env.sh
 
# Build cmake
    emcmake cmake -B ./build -S . -G Ninja

# Build
    cmake --build ./build -j -v
