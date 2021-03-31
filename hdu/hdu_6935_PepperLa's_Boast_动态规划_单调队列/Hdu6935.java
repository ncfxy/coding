import java.util.*;
import java.io.*;

public class Hdu6935 {

    public static void main(String[] args) {
        Hdu6935 m = new Hdu6935();
        try {
            m.solve1();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    int MAX = 1005;
    long map[][] = new long[MAX][MAX];
    int N, M;
    long K, U;
    Deque<Node> queues[] = new LinkedList[MAX];
    Deque<Node> rowQue = new LinkedList<>();

    long dp[][] = new long[MAX][MAX];

    public void solve1() throws IOException {
        for (int i = 0;i < MAX;i++) queues[i] = new LinkedList<>();
        NcfxyOjReader cin = new NcfxyOjReader(System.in);
//        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()) {
            N = cin.nextInt();
            M = cin.nextInt();
            K = cin.nextInt();
            U = cin.nextInt();
            for (int i = 1;i <= N;i++) {
                for (int j = 1;j <= M;j++) {
                    map[i][j] = cin.nextInt();
                    dp[i][j] = -1;
                }
            }
            for (int i = 1;i <= M;i++) queues[i].clear();
            dp[1][1] = map[1][1];
            for (int i = 1;i <= N;i++) {
                rowQue.clear();
                for (int j = 1; j<= M;j++) {
                    while(!queues[j].isEmpty() && queues[j].peek().rowNum < i - K)queues[j].poll();
                    while(!rowQue.isEmpty() && rowQue.peek().columnNum < j - K)rowQue.poll();
                    if (map[i][j] > 0) {
                        // 当前位置可以呼吸
                        if (dp[i-1][j] > 0)
                            dp[i][j] = Math.max(dp[i][j], dp[i-1][j] + map[i][j]);
                        if (dp[i][j-1] > 0)
                            dp[i][j] = Math.max(dp[i][j], dp[i][j-1] + map[i][j]);
                        if (dp[i-1][j-1] > 0)
                            dp[i][j] = Math.max(dp[i][j], dp[i-1][j-1] + map[i][j]);

                        // 寻找通过憋气来到当前位置
                        if (!queues[j].isEmpty()) {
                            dp[i][j] = Math.max(dp[i][j], queues[j].peek().maxBreath + map[i][j] - U);
                        }
                        if (!rowQue.isEmpty()) {
                            dp[i][j] = Math.max(dp[i][j], rowQue.peek().maxBreath + map[i][j] - U);
                        }
                    }

                    if (dp[i][j] >= U) {
                        while(!queues[j].isEmpty() && queues[j].peekLast().maxBreath <= dp[i][j])queues[j].pollLast();
                        queues[j].offer(new Node(dp[i][j], i, j));
                    }

                    if (!queues[j].isEmpty()) {
                        while(!rowQue.isEmpty() && rowQue.peekLast().maxBreath <= queues[j].peek().maxBreath)rowQue.pollLast();
                        rowQue.offer(queues[j].peek());
                    }

                }
            }
            System.out.println(dp[N][M]);
        }
    }

    public class Node {
        long maxBreath;
        int rowNum;
        int columnNum;
        public Node(long maxBreath, int rowNum, int columnNum) {
            this.maxBreath = maxBreath;
            this.rowNum = rowNum;
            this.columnNum = columnNum;
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
