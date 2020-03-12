
function findNumbersWithSum(data: number[], sum: number): [boolean, number|null, number|null] {
    let notFound: [boolean, number|null, number|null] = [false, null, null];
    if(data == null || data.length < 2) {
        return notFound;
    }
    let [left, right] = [0, data.length - 1];
    while(left < right) {
        let currentSum = data[left] + data[right];
        if(currentSum === sum) {
            return [true, data[left], data[right]];
        } else if (currentSum < sum) {
            left++;
        } else {
            right--;
        }
    }
    return notFound;
}

console.log(findNumbersWithSum([1,2,4,7,11,15], 15));