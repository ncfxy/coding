
function verifySequenceOfBst(sequence: number[]): boolean {
    if(sequence == null || sequence.length == 0) {
        return false;
    }
    let root = sequence[sequence.length - 1];
    let i = 0;
    for(;i < sequence.length-1;i++) {
        if(sequence[i] > root) {
            break;
        }
    }
    for(let j = i;j < sequence.length-1;j++) {
        if(sequence[j] < root) {
            return false;
        }
    }
    let confirmLeft = true;
    if(i > 0) {
        confirmLeft = verifySequenceOfBst(sequence.slice(0, i));
    }
    let confirmRight = true;
    if(i < sequence.length - 1) {
        confirmRight = verifySequenceOfBst(sequence.slice(i, sequence.length-1));
    }
    return confirmLeft && confirmRight;
}

console.log(verifySequenceOfBst([5,7,6,9,11,10,8]));
console.log(verifySequenceOfBst([7,4,6,5]));
console.log(verifySequenceOfBst([1,2,3,4,5,6]));
console.log(verifySequenceOfBst([6,5,4,3,2,1]));
