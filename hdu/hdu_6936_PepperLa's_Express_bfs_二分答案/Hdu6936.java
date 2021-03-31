import java.util.*;

public class Hdu6936 {
    public static void main(String[] args) {
        Hdu6936 m = new Hdu6936();
        m.solve1();
    }

    int MAX = 105;
    char map[][][] = new char[MAX][MAX][MAX];
    int dis[][][] = new int[MAX][MAX][MAX];
    int directionZ[] = new int[]{0, 0, 0, 0, -1, 1};
    int directionX[] = new int[]{0, 0, -1, 1, 0, 0};
    int directionY[] = new int[]{-1, 1, 0, 0, 0, 0};
    int Z, X, Y;

    int L, R;
    int mxd[] = new int[8];
    int operation[] = new int[]{-1, 1};
    int INF = 99999999;

    public void solve1() {

        Scanner cin = new Scanner(System.in);
        while (cin.hasNext()) {
            Z = cin.nextInt();
            X = cin.nextInt();
            Y = cin.nextInt();
            for (int z = 0; z < Z; z++) {
                for (int x = 0; x < X; x++) {
                    String line = cin.next();
                    map[z][x] = line.toCharArray();
                }
            }
            L = R = 0;
            bfs();
            while (L < R) {
                int mid = (L + R) >> 1;
                if (check(mid)) R = mid;
                else L = mid + 1;
            }
            System.out.println(L);
        }
    }

    // check 常数时间内检查是否有满足最大为ans的解法
    public boolean check(int ans) {
        int cnt = 0;
        for (int i = 0; i < 8; i++) mxd[i] = -INF;
        for (int z = 0; z < Z; z++) {
            for (int x = 0; x < X; x++) {
                for (int y = 0; y < Y; y++) {
                    if (dis[z][x][y] <= ans || map[z][x][y] != '*') continue;
                    ++cnt;
                    for (int i = 0; i < 8; i++) {
                        // 分别找最靠近八个角的user
                        mxd[i] = Math.max(mxd[i], z * operation[i & 1] + x * operation[i >> 1 & 1] + y * operation[i >> 2 & 1]);
                    }
                }
            }
        }
        if (cnt <= 0) {
            return true;
        }
        for (int z = 0; z < Z; z++) {
            for (int x = 0; x < X; x++) {
                for (int y = 0; y < Y; y++) {
                    if (map[z][x][y] == '.') {
                        int tmp = -INF;
                        for (int i = 0; i < 8; i++) {
                            tmp = Math.max(tmp, z * operation[i & 1] + x * operation[i >> 1 & 1] + y * operation[i >> 2 & 1] + mxd[i ^ 7]);
                        }
                        if (tmp <= ans)
                            return true;
                    }
                }
            }
        }
        return false;
    }

    public void bfs() {
        Queue<Node> queue = new LinkedList<>();
        for (int z = 0; z < Z; z++) {
            for (int x = 0; x < X; x++) {
                for (int y = 0; y < Y; y++) {
                    if (map[z][x][y] == '@') {
                        queue.offer(new Node(z, x, y));
                        dis[z][x][y] = 0;
                    } else {
                        dis[z][x][y] = -1;
                    }
                }
            }
        }
        while (!queue.isEmpty()) {
            Node node = queue.poll();
            R = Math.max(R, dis[node.z][node.x][node.y]);
            for (int i = 0; i < 6; i++) {
                int nextZ = node.z + directionZ[i];
                int nextX = node.x + directionX[i];
                int nextY = node.y + directionY[i];
                if (nextZ < 0 || nextX < 0 || nextY < 0 || nextZ > Z - 1 || nextX > X - 1 || nextY > Y - 1) {
                    continue;
                }
                if (dis[nextZ][nextX][nextY] == -1) {
                    dis[nextZ][nextX][nextY] = dis[node.z][node.x][node.y] + 1;
                    queue.offer(new Node(nextZ, nextX, nextY));

                }
            }
        }
    }

    class Node {
        int x, y, z;

        public Node(int z, int x, int y) {
            this.z = z;
            this.x = x;
            this.y = y;
        }
    }


}