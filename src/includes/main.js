
SudokuModule().then(mod => {
    const N = 9;
    const grid = document.getElementById("grid");
    // allocate 81 ints (4 bytes each) in WASM memory
    let ptr = mod._malloc(81 * 4);
    let heap = new Int32Array(mod.HEAP32.buffer, ptr, 81);  // allocate once

    // build the HTML table
    for (let r = 0; r < N; r++) {
        const row = grid.insertRow();
        for (let c = 0; c < N; c++) {
            const cell = row.insertCell();
            cell.dataset.row = r;
            cell.dataset.col = c;
            cell.contentEditable = false;  // toggle for user input

            cell.addEventListener("input", (e) => {
                const cell = e.target;
                const row = parseInt(cell.dataset.row, 10);
                const col = parseInt(cell.dataset.col, 10);
                const raw = cell.innerText.trim();
                const val = parseInt(raw, 10);

                // allow only 1–9, otherwise clear
                if (!/^[1-9]$/.test(raw)) {
                    cell.innerText = "";
                    heap[row * 9 + col] = 0;
                    cell.classList.remove("invalid");
                    return;
                }
                // Update heap
                heap[row * 9 + col] = val;

                // check with C logic: row, col, box
                const isValid = mod._is_valid_buffer(ptr, row, col, val);

                if (isValid) {
                    cell.classList.remove("invalid");
                } else {
                    cell.classList.add("invalid");
                }
            });
        }
    }
    /**
     * Description: Render the 9x9 puzzle grid.
     * Author: Patrick Duffany
     * Param: {Int32Array} heap        flat 81-element array of cell values
     * Param: {"given"|"solved"} mode  whether to mark cells as given or solved
     * Side-effects: manipulates cell.innerText and cell.classList
     * Vulnerability: Catching Exceptions [3-1] catches error if WASM-loading fails
     * Vulnerability: Information Leakage [5-1] using innerText vs innerHTML prevents injection of HTML/JS
     * Vulnerability: Information Leakage [5-2] prevent users from accessing the puzzle once solved
     */

    function renderGrid(heap, className = "", locked = true) {
        for (let idx = 0; idx < N * N; idx++) {
            const r = Math.floor(idx / N);
            const c = idx % N;
            const val = heap[idx];
            const cell = grid.rows[r].cells[c];
            cell.innerText = val || "";
            cell.className = val ? className : "";

            // style classes
            if (val) {
                cell.className = className;
            } else {
                cell.className = locked ? "" : "editable";
            }

            // control editability
            cell.contentEditable = !locked;
        }
    }
    // hook up the “New Puzzle” button
    document.getElementById("new").onclick = () => {
        const difficulty = parseInt(document.getElementById("difficulty").value, 10);

        if (ptr !== null) mod._free(ptr);
        ptr = mod._malloc(81 * 4); // reallocate
        heap = new Int32Array(mod.HEAP32.buffer, ptr, 81); // refresh view
        mod._generate_puzzle(ptr, difficulty);
        renderGrid(heap, "given", true);
        document.getElementById("solve").disabled = false; // reenable the solve button
        document.getElementById("play").disabled = false; // reenable the play button

    };
    // hook up the "Solve Puzzle" button
    document.getElementById("solve").onclick = () => {
        mod._fill_puzzle(ptr);
        renderGrid(heap, "solved");
        document.getElementById("solve").disabled = true; // disable to prevent multiple solves
        document.getElementById("play").disabled = true; // disable
    };
    document.getElementById("play").onclick = () => {
        renderGrid(heap, "given", false);
        document.getElementById("solve").disabled = false; // disable to prevent multiple solves
    };
    // generate one on load
    document.getElementById("new").click();
});