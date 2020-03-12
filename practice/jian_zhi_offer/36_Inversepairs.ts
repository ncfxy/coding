debugger;

function inversePairs(data: number[]) {
    if(data == null || data.length <= 0){
        return 0;
    }
    let copy = data.slice(0);
    const count = inversePairsCore(data, copy, 0, data.length-1);
    return count;
}

function inversePairsCore(data: number[], copy: number[], start: number, end: number): number {
    if (start === end) {
        copy[start] = data[start];
        return 0;
    }
    let length = ((end - start) >> 1);
    let left = inversePairsCore(copy, data, start, start + length);
    let right = inversePairsCore(copy, data, start + length + 1, end);

    let i = start + length;
    let j = end;
    let indexCopy = end;
    let count = 0;
    while(i >= start && j >= start + length + 1) {
        if(data[i] > data[j]) {
            copy[indexCopy--] = data[i--];
            count += j - start - length;
        } else {
            copy[indexCopy--] = data[j--];
        }
    }
    while(i >= start) {
        copy[indexCopy--] = data[i--];
    }
    while(j >= start + length + 1) {
        copy[indexCopy--] = data[j--];
    }
    return left + right + count;
}

const testData1 = [7,5,6,4];
console.log(inversePairs(testData1));
console.log(testData1);
const testData2 = [4,5,6,7];
console.log(inversePairs(testData2));
console.log(testData2);
const testData3 = [7,6,5,4];
console.log(inversePairs(testData3));
console.log(testData3);
