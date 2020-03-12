
function add(num1: number, num2: number): number {
    let sum, carry;
    do {
        sum = num1 ^ num2;
        carry = (num1 & num2) << 1;
        num1 = sum;
        num2 = carry;
    } while(num2 != 0);
    return num1;
}