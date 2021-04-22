import java.io.*;
import java.util.*;

public class Hdu6928 {
    public static void main(String[] args) {
        Hdu6928 m = new Hdu6928();
        try {
            m.solve1();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    int MAX = 200005;
    int x[] = new int[MAX];
    int c[] = new int[MAX];
    int INF = 1 << 30;
    int n, h, H;

    public void solve1() throws IOException {
        NcfxyOjReader cin = new NcfxyOjReader(System.in);
        while(cin.hasNext()) {
            int t = cin.nextInt();
            for (int i = 0; i < t; i++) {
                n = cin.nextInt();
                h = cin.nextInt();
                H = cin.nextInt();
                for (int j = 1; j <= n; j++) {
                    x[j] = cin.nextInt();
                }
                for (int j = 1; j <= n; j++) {
                    c[j] = cin.nextInt();
                }
                int minTime = INF;
                int minIndex = 1;
                for (int j = 1; j <= n; j++) {
                    int temp = x[j] % (2 * H);
                    int result = INF;
                    if (temp <= h || temp >= H - h) {
                        result = x[j] + c[j];
                    } else if (temp > h && temp < H - h) {
                        result = x[j] + c[j] + (H-h-temp);
                    }
                    if (result < minTime) {
                        minTime = result;
                        minIndex = j;
                    }
                }
                System.out.println(minIndex);
            }
        }
    }

    // 使用Java语言刷OJ经常超时的解决办法
// 用BufferReader类和StringTokenizer类代替Scanner类来读取输入
    public class NcfxyOjReader {
        BufferedReader reader;
        StringTokenizer tokenizer;

        public NcfxyOjReader(InputStream input) {
            reader = new BufferedReader(new InputStreamReader(input));
            tokenizer = new StringTokenizer("");
        }

        public boolean hasNext() {
            if (tokenizer.hasMoreTokens()) {
                return true;
            }
            while(!tokenizer.hasMoreTokens()) {
                try {
                    String line = reader.readLine();
                    if (line == null) {
                        return false;
                    }
                    tokenizer = new StringTokenizer(line);
                } catch (IOException e) {
                    return false;
                }
            }
            return true;
        }

        public String nextLine() throws Exception {
            return reader.readLine();
        }

        public String next() throws IOException {
            while ( ! tokenizer.hasMoreTokens() ) {
                tokenizer = new StringTokenizer(
                        reader.readLine() );
            }
            return tokenizer.nextToken();
        }

        public int nextInt() throws IOException {
            return Integer.parseInt( next() );
        }

        public double nextDouble() throws IOException {
            return Double.parseDouble( next() );
        }
    }
}