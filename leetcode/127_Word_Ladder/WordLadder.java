import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution {

    public int ladderLength(String beginWord, String endWord, List<String> wordList) {
        Map<String, Integer> map = new HashMap<String, Integer>();
        for(int i = 0;i < wordList.size();i++) {
            map.put(wordList.get(i), 9999999);
        }
        List<String> qu = new ArrayList<String>();
        qu.add(beginWord);
        map.put(beginWord, 1);
        while(qu.size() > 0){
            String current = qu.get(0);
            qu.remove(0);
            for(int i= 0;i < wordList.size();i++){
                String word = wordList.get(i);
                if(diff(current, word) == 1){
                    int currentCount = map.get(current);
                    int wordCount = map.get(word);
                    if(currentCount + 1 < wordCount){
                        map.put(word, currentCount + 1);
                        if(word.equals(endWord)){
                            return map.get(word);
                        }
                        qu.add(word);
                    }
                }
            }
        }
        return 0;
    }

    public int diff(String s1, String s2){
        int diffCount = 0;
        for(int i = 0;i < s1.length();i++){
            diffCount += s1.charAt(i) == s2.charAt(i) ? 0 : 1;
        }
        return diffCount;
    }

}

class MainClass {
    public static void main(String[] args){
        Solution s = new Solution();
        String begin = "hit";
        String end = "cog";
        List wordList = Arrays.asList("hot","dot","dog","lot","log","cog");
        int result = s.ladderLength(begin, end, wordList);
        System.out.println(result);
    }
}