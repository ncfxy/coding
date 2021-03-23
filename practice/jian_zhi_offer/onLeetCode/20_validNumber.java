package com.ncfxy;

class Solution {
    public boolean isNumber(String s) {
        s = s.trim();
        if(s.endsWith("e") || s.endsWith("E")) {
            return false;
        }
        String[] spiltedStrs = s.split("[eE]");
        if(spiltedStrs.length > 2) {
            return false;
        }
        if(spiltedStrs.length == 2) {
            return isDouble(spiltedStrs[0], true) && isInteger(spiltedStrs[1], true);
        }
        return isDouble(s, true);
    }

    public boolean isDouble(String s, boolean allowNegative) {
        if(s.length() <= 0) {
            return false;
        }
        if(s.charAt(0) == '.') {
            return isInteger(s.substring(1), false);
        }
        if(s.charAt(s.length() - 1) == '.') {
            return isInteger(s.substring(0, s.length() - 1), true);
        }
        if(s.charAt(0) == '+' || s.charAt(0) == '-') {
            return isDouble(s.substring(1), false);
        }
        String[] splitByPoint = s.split("\\.");
        if(splitByPoint.length > 2) {
            return false;
        } else if(splitByPoint.length == 2) {
            if(splitByPoint[0].length() + splitByPoint[1].length() == 0) {
                return false;
            }
            return isInteger(splitByPoint[0], true) && isInteger(splitByPoint[1], false);
        }
        return isInteger(s, true);
    }

    public boolean isInteger(String s, boolean allowNegative){
        if(s.trim().length() <= 0) {
            return false;
        }
        if(allowNegative && (s.charAt(0) == '+' || s.charAt(0) == '-')) {
            return isInteger(s.substring(1), false);
        }
        for(int i = 0;i < s.length();i++) {
            if(!(s.charAt(i) >= '0' && s.charAt(i) <= '9')) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Solution so = new Solution();

        System.out.println(so.isNumber("+100"));
        System.out.println(so.isNumber("5e2"));
        System.out.println(so.isNumber("-123"));
        System.out.println(so.isNumber("3.1416"));
        System.out.println(so.isNumber("0123"));
        System.out.println(so.isNumber("-1E-16"));
        System.out.println(so.isNumber("1 "));
        System.out.println(so.isNumber(".1 "));
        System.out.println(so.isNumber("3."));
        System.out.println(so.isNumber("+.8"));

        System.out.println("--------- false test cases ----------");
        System.out.println(so.isNumber("12e"));
        System.out.println(so.isNumber("1a3.14"));
        System.out.println(so.isNumber("1.2.3"));
        System.out.println(so.isNumber("+-5"));
        System.out.println(so.isNumber("12e+5.4"));
        System.out.println(so.isNumber("e9"));
        System.out.println(so.isNumber(". 1"));

    }
}
