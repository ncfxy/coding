
function isContinuousCards(numbers: number[]) {
    if(numbers == null || numbers.length < 1) {
        return false;
    }
    numbers.sort();
    let numberOfZero = 0;
    let numberOfGap = 0;
    for(let i = 0;i < numbers.length;i++) {
        if(numbers[i] === 0) {
            numberOfZero++;
        }
    }
    let small = numberOfZero;
    let big = small + 1;
    while(big < numbers.length) {
        if(numbers[small] === numbers[big]) {
            return false;
        }
        numberOfGap += numbers[big] - numbers[small] - 1;
        small++;
        big++;
    }
    return (numberOfZero >= numberOfGap) ? true: false;
}

console.log(isContinuousCards([1,2,3,4,5]));
console.log(isContinuousCards([1,3,4,5,6]));
console.log(isContinuousCards([1,3,4,5,0]));
console.log(isContinuousCards([1,2,2,3,0]));