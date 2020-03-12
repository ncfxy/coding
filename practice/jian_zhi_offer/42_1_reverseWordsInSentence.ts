

function reverseSentence(str: string) {
    if(str == null) {
        return null;
    }
    let result = str.split('').reverse().join('');
    let words = result.split(' ');
    let finalResult = words.map((word) => word.split('').reverse().join('')).join(' ');
    return finalResult;
}

console.log(reverseSentence('I am a student'));


function leftRotateString(str: string, n: number) {
    if(str == null) {
        return;
    }
    return str.slice(n) + str.slice(0, n);
}

console.log(leftRotateString('abcdefg',2));