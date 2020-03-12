
debugger;
function printProbability(number: number) {
    if(number < 1){
        return;
    }
    let maxValue = 6;
    let probabilities = new Array(2);
    probabilities[0] = new Array(maxValue * number + 1);
    probabilities[1] = new Array(maxValue * number + 1);
    let flag = 0;
    for(let i = 0;i <= maxValue * number;i++) {
        probabilities[flag][i] = (i >=1 && i <= maxValue) ? 1 : 0;
        probabilities[1-flag][i] = 0;
    } 
    for(let j = 2;j <= number;j++) {
        for(let i = 0;i < j; i++) {
            probabilities[1-flag][i] = 0;
        }
        for(let i = j;i <= maxValue * j;i++) {
            probabilities[1-flag][i] = 0;
            for(let x = 1; x <= i && x <= maxValue;x++) {
                probabilities[1-flag][i] += probabilities[flag][i-x];
            }
        }
        flag = 1 - flag;
    }
    let total = Math.pow(maxValue, number);
    for (let i = number;i <= maxValue * number;i++) {
        let ratio = probabilities[flag][i] / total;
        console.log('Sum ' + i + ': ' + ratio);
    }
}

printProbability(0);
printProbability(1);
printProbability(2);
printProbability(3);
printProbability(4);
printProbability(5);
printProbability(6);
