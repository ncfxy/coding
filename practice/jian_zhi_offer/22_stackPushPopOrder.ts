
function isPopOrder(pushArray: number[], popArray: number[]) {
    const dataStack: number[] = [];
    let pushIndex = 0, popIndex = 0;
    while(popIndex < popArray.length) {
        if(dataStack.length > 0 && dataStack[dataStack.length-1] === popArray[popIndex]){
            dataStack.pop();
            popIndex++;
        } else {
            if(pushIndex < pushArray.length) {
                dataStack.push(pushArray[pushIndex]);
                pushIndex++;
            } else {
                return false;
            }
        }
    }
    return true;
}

const pushArray = [1,2,3,4,5];
const popArray1 = [4,5,3,2,1];
const popArray2 = [4,3,5,1,2];
console.log(isPopOrder(pushArray, popArray1));
console.log(isPopOrder(pushArray, popArray2));
