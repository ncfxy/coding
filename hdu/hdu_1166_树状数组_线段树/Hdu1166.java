import java.util.*;
import java.io.*;

public class Hdu1166 {
    public static void main(String args[]) {
        Hdu1166 m = new Hdu1166();
        try {
            m.solve1();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void solve1() throws IOException{
        NcfxyOjReader cin = new NcfxyOjReader(System.in);
        // Scanner cin = new Scanner(System.in);
        int t = cin.nextInt();
        for (int i = 1; i <= t; i++) {
            int n = cin.nextInt();
            LineTreeNode root = new LineTreeNode(1, n, 0);
            buildTree(root);
            for (int j = 1; j <= n; j++) {
                int num = cin.nextInt();
                add(root, j, num);
            }
            System.out.println("Case " + i + ":");

            while (true) {
                String cmd = cin.next();
                if (cmd.equals("Add")) {
                    int loc = cin.nextInt();
                    int num = cin.nextInt();
                    add(root, loc, num);
                } else if (cmd.equals("Sub")) {
                    int loc = cin.nextInt();
                    int num = cin.nextInt();
                    add(root, loc, -num);
                } else if (cmd.equals("Query")) {
                    int start = cin.nextInt();
                    int end = cin.nextInt();
                    System.out.println(query(root, start, end));
                } else if (cmd.equals("End")) {
                    break;
                } else {
                    break;
                }
            }

        }
    }

    public void buildTree(LineTreeNode root) {
        if (root == null) {
            return;
        }
        if (root.left == root.right) {
            return;
        }
        int mid = (root.left + root.right) >> 1;
        LineTreeNode leftTreeNode = new LineTreeNode(root.left, mid, 0);
        LineTreeNode rightTreeNode = new LineTreeNode(mid+1, root.right, 0);
        buildTree(leftTreeNode);
        buildTree(rightTreeNode);
        root.leftTreeNode = leftTreeNode;
        root.rightTreeNode = rightTreeNode;
    }

    public void add(LineTreeNode root, int loc, int addCount) {
        if (root == null) {
            return;
        }
        if (root.left == root.right && root.left == loc) {
            root.sum += addCount;
            return;
        }
        int mid = (root.left + root.right) >> 1;
        if (loc <= mid) {
            add(root.leftTreeNode, loc, addCount);
        } else {
            add(root.rightTreeNode, loc, addCount);
        }
        root.sum = root.leftTreeNode.sum + root.rightTreeNode.sum;
    }

    public int query(LineTreeNode root, int start, int end) {
        if (root == null) {
            return 0;
        }
        if (root.right < start || root.left > end) {
            return 0;
        }
        if (root.left >= start && root.right <= end) {
            return root.sum;
        }
        int result = 0;
        result += query(root.leftTreeNode, start, end);
        result += query(root.rightTreeNode, start, end);
        return result;
    }

    public class LineTreeNode {
        LineTreeNode leftTreeNode;
        LineTreeNode rightTreeNode;
        int left;
        int right;
        int sum;

        public LineTreeNode(int left, int right, int sum) {
            this.left = left;
            this.right = right;
            this.sum = sum;
        }
    }

    class NcfxyOjReader {
        BufferedReader reader;
        StringTokenizer tokenizer;

        public NcfxyOjReader(InputStream input) {
            reader = new BufferedReader(new InputStreamReader(input));
            tokenizer = new StringTokenizer("");
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
