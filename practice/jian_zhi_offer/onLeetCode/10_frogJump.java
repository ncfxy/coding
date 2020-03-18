class Solution {
    private int[] resultBuffer = new int[102];
    private int MOD = 1000000007;

    public Solution() {
        resultBuffer[0] = resultBuffer[1] = 1;
        for(int i = 2;i < 102;i++) {
            resultBuffer[i] = (resultBuffer[i-2] + resultBuffer[i-1]) % MOD;
        }
    }

    public int fib(int n) {
        return resultBuffer[n];
    }
}