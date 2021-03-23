package com.ncfxy;

class Solution {
    public boolean isMatch(String s, String p) {
        if(s == null || p == null) {
            return false;
        }
        return isMatch(s, p, 0, 0);
    }

    public boolean isMatch(String s, String p, int sStartIndex, int pStartIndex) {
        if(sStartIndex >= s.length() && pStartIndex >= p.length()){
            return true;
        } else if(sStartIndex < s.length() && pStartIndex >= p.length()) {
            return false;
        } else if(sStartIndex >= s.length() && pStartIndex < p.length()) {
            if(pStartIndex + 1 < p.length() && p.charAt(pStartIndex + 1) == '*') {
                return isMatch(s,p, sStartIndex, pStartIndex + 2);
            } else {
                return false;
            }
        }
        boolean hasStarNext = false;
        boolean isPoint = false;
        if(p.charAt(pStartIndex) == '.') {
            isPoint = true;
        }
        if(pStartIndex + 1 < p.length() && p.charAt(pStartIndex + 1) == '*') {
            hasStarNext = true;
        }
        if(!hasStarNext && !isPoint) {
            if(s.charAt(sStartIndex) != p.charAt(pStartIndex)) {
                return false;
            } else {
                return isMatch(s, p, sStartIndex + 1, pStartIndex + 1);
            }
        }
        if(hasStarNext && !isPoint) {
            if(s.charAt(sStartIndex) != p.charAt(pStartIndex)) {
                return isMatch(s, p, sStartIndex, pStartIndex + 2);
            } else {
                return isMatch(s, p, sStartIndex + 1, pStartIndex + 2)
                        || isMatch(s, p, sStartIndex + 1, pStartIndex)
                        || isMatch(s, p, sStartIndex, pStartIndex + 2);
            }
        }
        if(!hasStarNext && isPoint) {
            return isMatch(s,p, sStartIndex + 1, pStartIndex + 1);
        }
        if(hasStarNext && isPoint) {
            return isMatch(s, p, sStartIndex + 1, pStartIndex + 2)
                    || isMatch(s, p, sStartIndex + 1, pStartIndex)
                    || isMatch(s, p, sStartIndex, pStartIndex + 2);
        }
        return false;
    }

    public static void main(String[] args) {
        Solution so = new Solution();
        System.out.println(so.isMatch("aa", "a"));
        System.out.println(so.isMatch("aa", "a*"));
        System.out.println(so.isMatch("ab", ".*"));
        System.out.println(so.isMatch("mississippi", "mis*is*p*."));
        System.out.println(so.isMatch("a", "ab*"));
        System.out.println(so.isMatch("bbbba", ".*a*a"));
    }


}
