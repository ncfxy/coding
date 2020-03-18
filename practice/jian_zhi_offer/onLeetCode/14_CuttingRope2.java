class Solution {

    public int cuttingRope(int n) {
        int MOD = 1000000007;
        if(n <= 3) {
            return n - 1;
        }
        int a = n / 3;
        int b = n % 3;
        if(b == 0) {
            return (int)(pow(3, a, MOD) % MOD);
        } else if(b == 1) {
            return (int)(pow(3, a - 1, MOD) * 4 % MOD);
        } else {
            return (int)(pow(3, a, MOD) * 2 % MOD);
        }
    }

    public long pow(long a, long b, long MOD) {
        long result = 1;
        while(b > 0) {
            if((b & 1) == 1) {
                result = result * a % MOD;
            }
            b >>= 1;
            a = a * a % MOD;
        }
        return (result % MOD);
    }


    public static void main(String[] args) {
        Solution so = new Solution();
        System.out.println(so.cuttingRope(2));
        System.out.println(so.cuttingRope(10));
        System.out.println(so.cuttingRope(1000));

        System.out.println(so.pow(3, 332, 1000000007));
    }
}