import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Hud6934 {
    public static void main(String[] args) {
        Hud6934 m = new Hud6934();
        try {
            m.solve1();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void solve1() throws IOException{
//        NcfxyOjReader cin = new NcfxyOjReader(System.in);
        Scanner cin = new Scanner(System.in);
        int t, n;
        while(cin.hasNext()) {
            t = cin.nextInt();
            for(int i = 0;i < t;i++) {
                n = cin.nextInt();
                if (n == 1) {
                    System.out.println(2);
                } else if (n == 2) {
                    System.out.println(16);
                } else if (n == 3) {
                    System.out.println(32);
                } else {
                    System.out.println(4);
                }
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
