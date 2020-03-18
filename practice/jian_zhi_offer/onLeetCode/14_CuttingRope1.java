package com.ncfxy;

import java.util.Map;

class Solution {
    private int[] resultBuffer = new int[60];

    public Solution() {
        resultBuffer[1] = 1;
        resultBuffer[2] = 1;
        resultBuffer[3] = 2;
        for(int i = 4;i < 60;i++) {
            resultBuffer[i] = (i-1);
            for(int j = 2;j <= i-j;j++) {
                int maxLeft = Math.max(resultBuffer[j], j);
                int maxRight = Math.max(resultBuffer[i-j], i-j);
                resultBuffer[i] = Math.max(resultBuffer[i], maxLeft * maxRight);
            }
        }
    }
    public int cuttingRope(int n) {
        return resultBuffer[n];
    }

    public int cuttingRopeAnswer(int n) {
        if(n <= 3) {
            return n - 1;
        }
        int a = n / 3;
        int b = n % 3;
        if(b == 0) {
            return (int)Math.pow(3, a);
        } else if(b == 1) {
            return ((int)Math.pow(3, a - 1)) * 4;
        } else {
            return (int)Math.pow(3, a) * 2;
        }
    }

    public static void main(String[] args) {
        Solution so = new Solution();
        System.out.println(so.cuttingRope(2));
        System.out.println(so.cuttingRope(10));
    }
}
