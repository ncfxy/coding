import java.io.*;
import java.util.*;

public class Hdu6929 {
    public static void main(String[] args) {
        Hdu6929 m = new Hdu6929();
        try {
            m.solve1();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    int T, N, K;

    public void solve1() throws IOException {
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()) {
            T = cin.nextInt();
            for(int i = 0; i < T; i++){
                N = cin.nextInt();
                K = cin.nextInt();
                long longOne = 1;
                long longList[] = new long[64];
                for (int j = 0; j < 64; j++) {
                    longList[j] = longOne << j;
                }
                if (N == 1 && K == 1) {
                    System.out.println(1);
                    continue;
                }
                if (K % 2 == 0 || N == K) {
                    System.out.println(-1);
                    continue;
                }
                List<Long> result = new ArrayList<>();
                result.add(longList[K] - 1);
                for (int j = 2; j <= K+1; j++) {
                    result.add(longList[K+1] - 1 - longList[K-j+1]);
                }
                for (int j = K+2; j <= N; j++) {
                    result.add(longList[j-1] + longList[K-1] - 1);
                }
                for (int j = 0; j < result.size() && j < N; j++) {
                    if (j > 0) {
                        System.out.print(" ");
                    }
                    System.out.print(result.get(j));
                }
                System.out.println();
            }
        }
    }
}

// 刚开始理解有问题，任意个数不能被其他数字异或得到