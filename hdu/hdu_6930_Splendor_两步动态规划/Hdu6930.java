import java.io.*;
import java.util.*;

public class Hdu6930 {
    public static void main(String[] args) {
        Hdu6930 m = new Hdu6930();
        try {
            m.solve1();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void solve1() throws IOException {
        NcfxyOjReader cin = new NcfxyOjReader(System.in);
//        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()) {
            int t = cin.nextInt();
            for(int i = 0;i < t;i++) {
                solve1ForOneCase(cin);
            }
        }
    }

    int INF = 1 << 30;
    int goal;

    public void solve1ForOneCase(NcfxyOjReader cin) throws IOException{
        int n = cin.nextInt();
        int m = cin.nextInt();
        goal = cin.nextInt();
        List<Card> cardList = new ArrayList<>();
        List<Pirate> pirateList = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            int p = cin.nextInt();
            int op = cin.nextInt();
            int k = cin.nextInt();
            Card card = new Card(p, op);
            for (int j = 0; j < k; j++) {
                int type = cin.nextInt();
                int count= cin.nextInt();
                card.setRequiredChip(type, count);
            }
            cardList.add(card);
        }
        for (int i = 0; i < m; i++) {
            int q = cin.nextInt();
            int b = cin.nextInt();
            Pirate pirate = new Pirate(q);
            for (int j = 0; j < b; j++) {
                int type = cin.nextInt();
                int count = cin.nextInt();
                pirate.setRequiredGems(type, count);
            }
            pirateList.add(pirate);
        }

        // 统计可能使用的5种筹码(chip)的最大值
        int maxChips[] = new int[6];
        for (int i = 1; i < 6; i++) {
            maxChips[i] = 5;  // 计算的时候比总数多5个
        }
        for (int i = 0; i < cardList.size(); i++) {
            Card card = cardList.get(i);
            for (int j = 1; j < 6; j++) {
                maxChips[j] += card.requireChips[j];
            }
        }

        int step[][][][][] = new int[maxChips[1]][maxChips[2]][maxChips[3]][maxChips[4]][maxChips[5]];
        for (int i = 0; i < maxChips[1]; i++) {
            for (int j = 0; j < maxChips[2]; j++) {
                for (int k = 0; k < maxChips[3]; k++) {
                    for (int l = 0; l < maxChips[4]; l++) {
                        for (int o = 0; o < maxChips[5]; o++) {
                            step[i][j][k][l][o] = INF; //初始化成极大值
                        }
                    }
                }
            }
        }
        step[0][0][0][0][0] = 0;
        int choice[][] = new int[][]{
                // 获取三个不同的筹码
                {0,1,1,1,0,0},
                {0,1,1,0,1,0},
                {0,1,1,0,0,1},
                {0,1,0,1,1,0},
                {0,1,0,1,0,1},
                {0,1,0,0,1,1},
                {0,0,1,1,1,0},
                {0,0,1,1,0,1},
                {0,0,1,0,1,1},
                {0,0,0,1,1,1},
                // 获取两个相同的筹码
                {0,2,0,0,0,0},
                {0,0,2,0,0,0},
                {0,0,0,2,0,0},
                {0,0,0,0,2,0},
                {0,0,0,0,0,2},
        };
        for (int i = 0; i < maxChips[1]; i++) {
            for (int j = 0; j < maxChips[2]; j++) {
                for (int k = 0; k < maxChips[3]; k++) {
                    for (int l = 0; l < maxChips[4]; l++) {
                        for (int o = 0; o < maxChips[5]; o++) {
                            // 获取三个不同的筹码
                            for (int p = 0; p < choice.length; p++) {
                                if (i - choice[p][1] >= 0 && j - choice[p][2] >= 0 && k - choice[p][3] >= 0 && l - choice[p][4] >= 0 && o - choice[p][5] >= 0) {
                                    step[i][j][k][l][o] = Math.min(step[i][j][k][l][o], step[i-choice[p][1]][j-choice[p][2]][k-choice[p][3]][l-choice[p][4]][o-choice[p][5]] + 1);
                                }
                            }
                        }
                    }
                }
            }
        }

        // 倒叙补充之前未覆盖的组合
        int choice2[][] = new int[][]{
                {0,1,0,0,0,0},
                {0,0,1,0,0,0},
                {0,0,0,1,0,0},
                {0,0,0,0,1,0},
                {0,0,0,0,0,1},
        };
        for (int i = maxChips[1]-1;i >= 0; i--) {
            for (int j = maxChips[2]-1; j>=0;j--) {
                for (int k = maxChips[3]-1; k>=0;k--) {
                    for (int l = maxChips[4]-1; l>=0;l--) {
                        for (int o = maxChips[5]-1; o>=0;o--) {
                            for (int p = 0; p < choice2.length; p++) {
                                if(i+choice2[p][1] < maxChips[1] && j+choice2[p][2] < maxChips[2] & k+choice2[p][3] < maxChips[3]&&l+choice2[p][4]<maxChips[4] && o+choice2[p][5] < maxChips[5]){
                                    step[i][j][k][l][o] = Math.min(step[i][j][k][l][o], step[i+choice2[p][1]][j+choice2[p][2]][k+choice2[p][3]][l+choice2[p][4]][o+choice2[p][5]]);
                                }
                            }
                        }
                    }
                }
            }
        }
        
        int pirateScore[][][][][] = new int[10][10][10][10][10];
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    for (int l = 0; l < 10; l++) {
                        for (int o = 0; o < 10; o++) {
                            pirateScore[i][j][k][l][o] = 0;
                            for (int p = 0; p < pirateList.size(); p++) {
                                Pirate pirate = pirateList.get(p);
                                if(i >= pirate.requiredGems[1] && j >= pirate.requiredGems[2] && k >= pirate.requiredGems[3] && l >= pirate.requiredGems[4] && o >= pirate.requiredGems[5]) {
                                    pirateScore[i][j][k][l][o] += pirate.score;
                                }
                            }
                        }
                    }
                }
            }
        }
        boolean selectTag[] = new boolean[cardList.size()+1];
        int result = solve1Dfs(cardList, step, pirateScore, 0, selectTag);
        if (result < INF) {
            System.out.println(result);
        } else {
            System.out.println(-1);
        }
    }

    public int solve1Dfs(List<Card> cardList, int step[][][][][], int pirateScore[][][][][], int depth, boolean selectTag[]) {
        if (depth >= cardList.size()) {
            int selectCardCount = 0;
            int totalScore = 0;
            int needChips[] = new int[]{0,0,0,0,0,0};
            int finalGems[] = new int[]{0,0,0,0,0,0};
            for (int i = 0; i < cardList.size(); i++) {
                if(selectTag[i]) {
                    selectCardCount++;
                    totalScore += cardList.get(i).score;
                    for (int j = 0; j < 6; j++) {
                        needChips[j] += cardList.get(i).requireChips[j];
                    }
                    finalGems[cardList.get(i).kind]++;
                }
            }
            totalScore += pirateScore[finalGems[1]][finalGems[2]][finalGems[3]][finalGems[4]][finalGems[5]];
            if (totalScore < goal) {
                return INF;
            }
            int finalStep = selectCardCount + step[needChips[1]][needChips[2]][needChips[3]][needChips[4]][needChips[5]];
            return finalStep;
        }

        int minStep = INF;
        selectTag[depth] = true;
        int result1 = solve1Dfs(cardList, step, pirateScore, depth+1, selectTag);
        minStep = Math.min(minStep, result1);

        selectTag[depth] = false;
        int result2 = solve1Dfs(cardList, step, pirateScore, depth+1, selectTag);
        minStep = Math.min(minStep, result2);
        return minStep;
    }

    public class Card {
        int score;
        int kind;
        int requireChips[];
        public Card(int score, int kind) {
            this.score = score;
            this.kind = kind;
            this.requireChips = new int[]{0,0,0,0,0,0};
        }
        public void setRequiredChip(int type, int count) {
            this.requireChips[type] =count;
        }
    }

    public class Pirate {
        int score;
        int requiredGems[];
        public Pirate (int score) {
            this.score = score;
            this.requiredGems = new int[6];
        }
        public void setRequiredGems(int type, int count) {
            this.requiredGems[type] = count;
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

// 第一步动态规划， 统计出step[white][blue][red][green][black]所需的最小步数
// 第二步统计出pirateScore[white][blue][red][green][black]可以拿到的分数
// 第三步dfs搜索所有卡牌的组合