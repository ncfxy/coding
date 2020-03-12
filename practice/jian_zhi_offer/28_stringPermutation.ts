

function permutation(str: string[]) {
    if(str == null || str.length === 0) {
        return ;
    }
    permutationRecursive(str, 0);
}

function permutationRecursive(str: string[], currentIndex: number) {
    if(currentIndex === str.length - 1) {
        console.log(str);
    }
    for(let i = currentIndex;i < str.length;i++) {
        [str[i], str[currentIndex]] = [str[currentIndex], str[i]];
        permutationRecursive(str, currentIndex + 1);
        [str[i], str[currentIndex]] = [str[currentIndex], str[i]];
    }
}

permutation(['a','b','c']);
