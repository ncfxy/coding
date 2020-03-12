debugger;

function printMatrixClockwisely(numbers: number[][] | null) {
    if(numbers == null || numbers.length <= 0 || numbers[0].length <= 0) {
        return;
    }
    let start = 0;
    let rows = numbers.length;
    let columns = numbers[0].length;
    while(start * 2 < columns && start * 2 < rows) {
        printMatrixInCircle(numbers, columns, rows, start);
        start++;
    }
}

function printMatrixInCircle(numbers: number[][], columns: number, rows: number, start: number) {
    let endX = columns - 1 - start;
    let endY = rows - 1 - start;
    let result = [];
    // left to right
    for(let i = start; i <= endY;i++) {
        result.push(numbers[start][i]);
    }
    // top to bottom
    if(start < endY){
        for(let i = start+1; i <= endY;i++) {
            result.push(numbers[i][endX]);
        }
    }
    // right to left
    if(start < endX && start < endY) {
        for(let i = endX - 1;i >= start;i--){
            result.push(numbers[endY][i]);
        }
    }
    // bottom to top
    if(start < endX && start < endY - 1) {
        for (let i = endY - 1;i >= start + 1;i--) {
            result.push(numbers[i][start]);
        }
    }
    console.log(result);
}

const data = [
    [1,2,3,4],
    [5,6,7,8],
    [9,10,11,12],
    [13,14,15,16]
];

console.log(printMatrixClockwisely(data));

const data2 = [
    [1,2,3],
    [4,5,6],
    [7,8,9]
]

console.log(printMatrixClockwisely(data2));