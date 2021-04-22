import java.io.*;
import java.util.*;

public class Hdu6932 {
    public static void main(String[] args) {
        Hdu6932 m = new Hdu6932();
        try {
            m.solve1();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void solve1() throws IOException {
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()) {
            String str = cin.next();
            List<Node> list = new ArrayList<>();
            if (str.length() <= 0) {
                System.out.println("");
                continue;
            }
            char currentChar = str.charAt(0);
            Node node = new Node(currentChar, 1);
            for (int i = 1;i < str.length();i++) {
                if (str.charAt(i) == node.ch) {
                    node.count++;
                } else {
                    list.add(node);
                    currentChar = str.charAt(i);
                    node = new Node(currentChar, 1);
                }
            }
            list.add(node);
            findBestAnswer(list);
            StringBuilder builder = new StringBuilder();
            for (int i = 0;i < list.size();i++) {
                Node tempNode = list.get(i);
                if (tempNode.count <= 0 ){
                    continue;
                } else if (tempNode.count == 1) {
                    builder.append(tempNode.ch);
                    continue;
                } else {
                    builder.append(tempNode.ch);
                    builder.append(intToHex(tempNode.count));
                }
            }
            System.out.println(builder.toString());
        }
    }

    public void findBestAnswer(List<Node> list) {
        boolean canDecrease = false;
        boolean firstChoose = false;
        Node bestCutNode = null;
        for(int i = 0 ;i < list.size();i++) {
            Node node = list.get(i);
            if (node.count == 1) {
                canDecrease = true;
                bestCutNode = node;
                if (i + 1 < list.size() && list.get(i+1).ch < node.ch) {
                    // 如果下一个字母的字母序更小的话，则直接为最优解
                    break;
                }
            } else if (node.count == 2) {
                canDecrease = true;
                bestCutNode = node;
                if (i + 1 < list.size() && list.get(i+1).ch < '2') {
                    // 如果下一个字母的字母序比2更小的话，则直接为最优解
                    break;
                }
            } else if (canDivideBy16(node.count)) {
                canDecrease = true;
                bestCutNode = node;
                // 从1000变成FFF，字母序会变大
            }
            if (canDecrease == false && firstChoose == false) {
                // 如果当前没有可以变短的方案，才会考虑,选中第一个之后不再选其他的
                bestCutNode = node;
                firstChoose = true;
            }
        }
        bestCutNode.count--;
        return;
    }

    public boolean canDivideBy16(int count) {
        while(count > 1) {
            int temp = count % 16;
            if (temp != 0 ) {
                return false;
            }
            count = count / 16;
        }
        return true;
    }

    public String intToHex(int count) {
        String hex = "0123456789ABCDEF";
        StringBuilder build = new StringBuilder();
        while(count > 0) {
            int temp = count % 16;
            build.insert(0, hex.charAt(temp));
            count = count / 16;
        }
        return build.toString();
    }

    public class Node {
        char ch;
        int count;
        public Node(char ch, int count) {
            this.ch = ch;
            this.count = count;
        }
    }
}

// TestCases:
// aaacccccccccc a2cA
// aaaccccccccccccccc a2cF
// aaacccccccccccccccc a3cF
// aaabaaa a3a3
// aaabcccd a3b1c3