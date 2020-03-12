
function getFirstK(data: number[], k: number, start: number, end: number): number {
    if(start > end){
        return -1;
    }
    let middleIndex = (start + end) >> 1;
    let middleData = data[middleIndex];
    if(middleData === k) {
        if((middleIndex > 0 && data[middleIndex - 1] != k)) {
            return middleIndex;
        } else {
            end = middleIndex - 1;
        }
    } else if(middleData < k) {
        start = middleIndex + 1;
    } else {
        end = middleIndex - 1;
    }
    return getFirstK(data, k, start, end);
}

function getLastK(data: number[], k: number, start: number, end: number): number{
    if(start > end || start < 0 || end >= data.length) {
        return -1;
    }
    let middleIndex = (start + end) >> 1;
    let middleData = data[middleIndex];
    if(middleData === k) {
        if(middleIndex < data.length - 1 && data[middleIndex + 1] != k) {
            return middleIndex;
        } else {
            start = middleIndex + 1;
        }
    } else if(middleData < k) {
        start = middleIndex + 1;
    } else {
        end = middleIndex - 1;
    }
    return getLastK(data, k, start, end);
}

function getNumberOfK(data: number[], k: number) {
    let number: number = 0;
    if(data != null && data.length > 0) {
        let first = getFirstK(data, k, 0, data.length -1);
        let last = getLastK(data, k, 0, data.length -1);
        if(first > -1 && last > -1) {
            number = last - first + 1;
        }
    }
    return number;
}

const testData38_1 = [1,2,3,3,3,3,3,4,5];
console.log(getNumberOfK(testData38_1, 3));