debugger;
function print1ToMaxofDigits_1(n: number) {
    if (n <= 0) {
        return;
    }
    let number: string[] = new Array(n);
    for (let i = 0; i < n; i++) {
        number[i] = '0';
    }
    while (!increment(number)) {
        PrintNumber(number);
    }
}

function increment(number: string[]) {
    let isOverflow = false;
    let nTakeOver = 0;
    let length = number.length;
    for (let i = length - 1; i >= 0; i--) {
        let nSum = number[i].charCodeAt(0) - '0'.charCodeAt(0) + nTakeOver;
        if (i === length - 1) {
            nSum++;
        }
        if (nSum >= 10) {
            if (i === 0) {
                isOverflow = true;
            } else {
                nSum -= 10;
                nTakeOver = 1;
                number[i] = String.fromCharCode('0'.charCodeAt(0) + nSum);
            }
        } else {
            number[i] = String.fromCharCode('0'.charCodeAt(0) + nSum);
            break;
        }
    }
    return isOverflow;
}

function PrintNumber(number: string[]) {
    let isBeginning0 = true;
    let length = number.length;
    let result = '';
    for (let i = 0; i < length; i++) {
        if(isBeginning0 && number[i] !== '0') {
            isBeginning0 = false;
        }
        if(!isBeginning0) {
            result += number[i];
        }
    }
    console.log(result);
}

print1ToMaxofDigits_2(3);
print1ToMaxofDigits_2(0);
print1ToMaxofDigits_2(-1);

function print1ToMaxofDigits_2(n: number) {
    if (n <= 0) {
        return;
    }
    let zeroCharCode = '0'.charCodeAt(0);
    let number: string[] = new Array(n);
    for (let i = 0;i < n;i++) {
        number[i] = '0';
    }
    for (let i = 0;i < 10;i++) {
        number[0] = String.fromCharCode(zeroCharCode + i);
        printToMaxOfNDigitsRecursively(number, 0);
    }
}

function printToMaxOfNDigitsRecursively(number: string[], index: number) {
    if(index === number.length - 1){
        PrintNumber(number);
        return;
    }
    let zeroCharCode = '0'.charCodeAt(0);
    for (let i = 0;i < 10;i++) {
        number[index + 1] = String.fromCharCode(zeroCharCode + i);
        printToMaxOfNDigitsRecursively(number, index + 1);
    }
}
