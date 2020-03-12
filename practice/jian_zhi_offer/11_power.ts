
function power(base: number, exponent: number) {
    let invalideInput = false;
    if (equal(base, 0.0) && exponent < 0) {
        invalideInput = true;
        return 0.0;
    }
    let absExponent = Math.abs(exponent);
    let result = powerWithUnsignedExponent(base, absExponent);
    if (exponent < 0) {
        result = 1.0 / result;
    }
    return result;
}

function powerWithUnsignedExponent(base: number, exponent: number) {
    if (exponent === 0) {
        return 1;
    }
    if (exponent === 1) {
        return base;
    }
    let result: number = powerWithUnsignedExponent(base, exponent >> 1);
    result *= result;
    if ((exponent & 1) === 1) {
        result *= base;
    }
    return result;
}

function powerWithUnsignedExponent2(base: number, exponent: number) {
    if (exponent === 0) {
        return 1;
    }
    if (exponent === 1) {
        return base;
    }
    let result = 1;
    let tempBase = base, tmpExponent = exponent;
    while(tmpExponent) {
        if((tmpExponent & 1) === 1) {
            result *= tempBase;
        }
        tmpExponent >>= 1;
        tempBase *= tempBase;
    }
    return result;
}

function equal(num1: number, num2: number) {
    if ((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001)) {
        return true;
    } else {
        return false;
    }
}

console.log(power(2,10));

console.log(power(2,-10));

console.log(power(0,-8));
