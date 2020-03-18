class Solution {
    public double myPow(double x, int n) {
        if(n == -2147483648) {
            return 1 / myPow(x, 2147483647) / x;
        }
        if(n < 0) {
            return 1 / myPow(x, -n);
        }
        double result = 1.0;
        while(n > 0) {
            if((n & 1) == 1) {
                result *= x;
            }
            n >>= 1;
            x *= x;
        }
        return result;
    }
}