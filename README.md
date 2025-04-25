Follow these steps to configure the application's front end.

1. Install & configure Emscripten: <br />
    git clone https://github.com/emscripten-core/emsdk.git <br />
    cd emsdk <br />

    *Note: If you are getting an error when trying to run the scripts <br />
     try inputting to give permission: Set-ExecutionPolicy Bypass -Scope Process -Force <br />

    ./emsdk install latest <br />
    ./emsdk activate latest <br />

    For Windows: <br />
        ./emsdk_env.bat <br />

    Linux/Other: <br />
       source ./emsdk_env.sh <br />

2. Verify that the emsdk is installed: <br />
    emcc -v <br />

3. Compile the code to WebAssembly: <br />
    emcc sudoku.c wasm_api.c \ <br />
        -O3 \
        -s WASM=1 \
        -s MODULARIZE=1 \
        -s EXPORT_NAME="SudokuModule" \
        -s EXPORTED_FUNCTIONS='["_malloc","_free","_generate_puzzle","_fill_puzzle","_is_valid_buffer"]' \
        -s EXPORTED_RUNTIME_METHODS='["HEAP32"]' \
        -o sudoku.js

4. Serve & Test: (In the directory with index.html & sudoku.js) <br />
    python3 -m http.server 8080 <br />
   
![image](https://github.com/user-attachments/assets/8d483309-249b-4624-9c64-99119b2c4637)
