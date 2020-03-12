

const dataStack: any[] = [];
const minStack: any[] = [];

function push(val: any) {
    dataStack.push(val);
    let currentMin = min();
    if(currentMin && currentMin < val) {
        minStack.push(currentMin);
    } else {
        minStack.push(val);
    }
}

function pop(): any {
    if(dataStack.length > 0 && minStack.length > 0) {
        dataStack.pop();
        minStack.pop();
    }
}

function min(): any {
    if(minStack.length > 0){
        return minStack[minStack.length-1];
    } 
    return null;
}

console.log(dataStack);
push(3);
push(4);
console.log(dataStack);
console.log(min());
push(2);
console.log(dataStack);
console.log(min());
push(1);
console.log(dataStack);
console.log(min());
pop();
console.log(dataStack);
console.log(min());