debugger;
function findNumsAppearOnce(data: number[]): [number|null, number|null] {
    if(data == null || data.length < 2) {
        return [null, null];
    }
    let resultExclusiveOR = 0;
    for(let i = 0;i < data.length;i++) {
        resultExclusiveOR ^= data[i];
    }
    let indexOf1 = findFirstBitIs1(resultExclusiveOR);
    let number1 = 0, number2 = 0;
    for(let i = 0;i < data.length;i++) {
        if(isBit1(data[i], indexOf1)) {
            number1 ^= data[i];
        } else {
            number2 ^= data[i];
        }
    }
    return [number1, number2];
}

function findFirstBitIs1(num: number) {
    if(num === 0) {
        return -1;
    }
    let indexBit = 0;
    let temp = 1;
    while(temp > 0 && (num & temp) === 0){
        temp <<= 1;
        indexBit++;
    }
    return indexBit;
}

function isBit1(num: number, indexBit: number) {
    let temp = (1 << indexBit);
    return (num & temp) !== 0;
}

console.log(findNumsAppearOnce([2,4,3,6,3,2,5,5]));
