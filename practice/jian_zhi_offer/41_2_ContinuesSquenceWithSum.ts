
function findContinuousSequence(sum: number) {
    if(sum < 3) {
        return;
    }
    let small = 1;
    let big = 2;
    let middle = (1 + sum) >> 1;
    let currentSum = small + big;
    while(small < middle) {
        if(currentSum === sum) {
            printContinuousSequence(small, big);
        }
        while(currentSum > sum && small < middle){
            currentSum -= small;
            small++;
            if(currentSum === sum) {
                printContinuousSequence(small, big);
            }
        }
        big++;
        currentSum += big;
    }
}

function printContinuousSequence(small: number, big: number) {
    let result: number[] = [];
    for (let i = small; i <= big;i++) {
        result.push(i);
    }
    console.log(result);
}

findContinuousSequence(9);
findContinuousSequence(13);
findContinuousSequence(4);
findContinuousSequence(0);