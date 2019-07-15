/**
 * @param {string} beginWord
 * @param {string} endWord
 * @param {string[]} wordList
 * @return {number}
 */
var ladderLength = function(beginWord, endWord, wordList) {
    var map = {};
    wordList.forEach((word) => {
        map[word] = 999999;
    });
    map[beginWord] = 1;
    var qu = [];
    qu.push(beginWord);
    while(qu.length > 0){
        var current = qu[0];
        qu = qu.slice(1);
        wordList.forEach((word) => {
            if(diff(current, word) === 1) {
                var currentCount = map[current];
                var wordCount = map[word];
                if(currentCount + 1 < wordCount) {
                    map[word] = currentCount + 1;
                    qu.push(word);
                }
            }
        });
        if(map[endWord] && map[endWord] < 999999){
            return map[endWord];
        }
    }
    return map[endWord] && map[endWord] < 999999 ? map[endWord] : 0;
};

var diff = function(s1, s2) {
    var diffCount = 0;
    for(var i = 0;i < s1.length;i++){
        diffCount += s1[i] == s2[i] ? 0 : 1;
    }
    return diffCount
}

function test() {
    var beginWord = 'hit';
    var endWord = 'cog';
    wordList = ['hot','dot','dog','lot','log','cog'];
    var result = ladderLength(beginWord, endWord, wordList);
    console.log(result);
}

test();