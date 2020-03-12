debugger;

function firstNotRepeatingChar(str: string|null) {
    if(str == null) {
        return null;
    }
    let hashTable: number[] = new Array(257);
    for(let i = 0;i < 257;i++) {
        hashTable[i] = 0;
    }
    for(let i = 0;i < str.length;i++) {
        hashTable[str.charCodeAt(i)]++;
    }
    for(let i = 0;i < str.length;i++) {
        if(hashTable[str.charCodeAt(i)] === 1) {
            return str.charAt(i);
        }
    }
    return null;
}

console.log(firstNotRepeatingChar(null));
console.log(firstNotRepeatingChar('abcac'));
console.log(firstNotRepeatingChar('abcdefg'));
console.log(firstNotRepeatingChar('abcabc'));