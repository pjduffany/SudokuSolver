Follow these steps to configure the application's front end.

1. Install & configure Emscripten:
    git clone https://github.com/emscripten-core/emsdk.git
    cd emsdk
    ./emsdk install latest
    ./emsdk activate latest
    source ./emsdk_env.sh

2. Verify that the emsdk is installed:
    emcc -v

3. Compile the code to WebAssembly:
    emcc sudoku.c wasm_api.c \
        -O3 \
        -s WASM=1 \
        -s MODULARIZE=1 \
        -s EXPORT_NAME="SudokuModule" \
        -s EXPORTED_FUNCTIONS='["_malloc","_free","_generate_puzzle","_fill_puzzle"]' \
        -s EXPORTED_RUNTIME_METHODS='["HEAP32"]' \
        -o sudoku.js

4. Serve & Test: (In the directory with index.html & sudoku.js)
   python3 -m http.server 8080
   Navigate to localhost:8080/index.html to see access the page

![image](https://github.com/user-attachments/assets/6b312ead-1742-4c31-9bad-1c8298838688)
