import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

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