import java.io.*;
import java.util.*;

public class Hdu6931 {
    public static void main(String[] args) {
        Hdu6931 m = new Hdu6931();
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
            for (int i = 0;i < t;i++) {
                solve1ForOneCase(cin);
            }
        }
    }

    public void solve1ForOneCase(Scanner cin) {
        int n = cin.nextInt();
        int k = cin.nextInt();
        int result = 0;
        Card cards[] = new Card[k];
        for (int i = 0;i < k;i++) {
            cards[i] = null;
        }
        for (int i = 0;i < n;i++) {
            String str = cin.next();
            int count = cin.nextInt();
            cards[i % k] = new Card(str, count);
            result += countCard(cards, k);
        }
        System.out.println(result);
    }

    public int countCard(Card cards[], int k) {
        int counts[] = new int[4];
        int result = 0;
        for (int i = 0;i < k;i++) {
            if (cards[i] != null) {
                if (cards[i].str.equals("A")) {
                    counts[0] += cards[i].count;
                } else if (cards[i].str.equals("B")) {
                    counts[1] += cards[i].count;
                } else if (cards[i].str.equals("G")) {
                    counts[2] += cards[i].count;
                } else if (cards[i].str.equals("P")) {
                    counts[3] += cards[i].count;
                }
            }
        }
        for (int i = 0;i < 4;i++) {
            if (counts[i] == 5) {
                result++;
            }
        }
        return result;
    }

    public class Card {
        String str;
        int count;
        public Card(String str, int count) {
            this.str = str;
            this.count = count;
        }
    }
}