 debugger;
 function reorderOddEven(pData: number[]) {
     if(pData == null || pData.length === 0) {
         return;
     }
     let [left, right] = [0, pData.length -1];
     while(left < right) {
         while(left < pData.length && (pData[left] & 1) !== 0) {
             left++;
         }
         while(right >= 0 && (pData[right] & 1) === 0) {
             right--;
         }
         if(left < right) {
             [pData[left], pData[right]] = [pData[right], pData[left]];
         }
     }
 }

 const array = [4,3,5,6,7,8,9,10];
 reorderOddEven(array)
 console.log(array);

 function reorderOddEvenUpdate(pData: number[], judgeFunction: (data: number) => boolean) {
    if(pData == null || pData.length === 0) {
        return;
    }
    let [left, right] = [0, pData.length -1];
    while(left < right) {
        while(left < pData.length && !judgeFunction.call(null, pData[left])) {
            left++;
        }
        while(right >= 0 && judgeFunction.call(null, pData[right])) {
            right--;
        }
        if(left < right) {
            [pData[left], pData[right]] = [pData[right], pData[left]];
        }
    }
}

function isEven(data: number) {
    return (data & 1) === 0;
}

const array1 = [4,3,5,6,7,8,9,10];
reorderOddEvenUpdate(array1, isEven);
console.log(array1);
