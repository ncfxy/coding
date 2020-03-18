class Solution {
    public int[] printNumbers(int n) {
        int all = 1;
        for(int i = 0;i < n;i++) {
            all *= 10;
        }
        int[] result = new int[all - 1];
        for(int i = 1;i < all;i++) {
            result[i-1] = i;
        }
        return result;
    }
}