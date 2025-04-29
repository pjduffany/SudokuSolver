
SudokuModule().then(mod => {
    const N = 9;
    const grid = document.getElementById("grid");
    let ptr = mod._malloc(81 * 4);
    let heap = new Int32Array(mod.HEAP32.buffer, ptr, 81);

    // build the HTML table
    for (let r = 0; r < N; r++) {
        const row = grid.insertRow();
        for (let c = 0; c < N; c++) {
            const cell = row.insertCell();
            cell.dataset.row = r;
            cell.dataset.col = c;
            cell.contentEditable = false;

            cell.addEventListener("input", (e) => {
                const cell = e.target;
                const row = parseInt(cell.dataset.row, 10);
                const col = parseInt(cell.dataset.col, 10);
                const raw = cell.innerText.trim();
                const val = parseInt(raw, 10);

               
                if (!/^[1-9]$/.test(raw)) {
                    cell.innerText = "";
                    heap[row * 9 + col] = 0;
                    cell.classList.remove("invalid");
                    return;
                }

                heap[row * 9 + col] = val;

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
     * Param: {Int32Array} heap        flat 81-element array of cell values
     * Param: {"given"|"solved"} mode  whether to mark cells as given or solved
     * Side-effects: manipulates cell.innerText and cell.classList
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

            
            cell.contentEditable = !locked && !val;
        }
    }
    // hook up the “New Puzzle” button
    document.getElementById("new").onclick = () => {
        const difficulty = parseInt(document.getElementById("difficulty").value, 10);

        if (ptr !== null) mod._free(ptr);
        ptr = mod._malloc(81 * 4);
        heap = new Int32Array(mod.HEAP32.buffer, ptr, 81); 
        mod._generate_puzzle(ptr, difficulty);
        renderGrid(heap, "given", true);
        document.getElementById("solve").disabled = false; 
        document.getElementById("play").disabled = false; 

    };
    // hook up the "Solve Puzzle" button
    document.getElementById("solve").onclick = () => {
        mod._fill_puzzle(ptr);
        renderGrid(heap, "solved");
        document.getElementById("solve").disabled = true; 
        document.getElementById("play").disabled = true; 
    };
    document.getElementById("play").onclick = () => {
        renderGrid(heap, "given", false);
        document.getElementById("solve").disabled = false;
    };
    // generate one on load
    document.getElementById("new").click();
});