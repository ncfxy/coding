import java.io.*;
import java.util.*;

public class Hdu6927 {
    public static void main(String[] args) {
        Hdu6927 m = new Hdu6927();
        try {
            m.solve1();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void solve1() throws IOException {
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()) {
            int t = cin.nextInt();
            for(int index = 0;index < t;index++) {
                long n = cin.nextInt();
                long m = cin.nextInt();
                long sum = 0;
                for (int i = 1; i <= m; i++) {
                    long nextN = cal(n);
                    sum += nextN;
                    if (nextN == n) {
                        sum += n * (m-i);
                        break;
                    }
                    n = nextN;
                }
                System.out.println(sum);
            }
        }
    }

    public long cal(long num) {
        long ans = num;
        long tmp = 10;
        while(tmp < num) {
            ans *= (num % tmp);
            ans %= (num + 1);
            tmp *= 10;
        }
        return ans % (num + 1);
    }
}