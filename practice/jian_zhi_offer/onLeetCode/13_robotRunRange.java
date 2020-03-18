class Solution {
    public int movingCount(int m, int n, int k) {
        boolean[][] cover = new boolean[m][n];
        for(int i = 0;i < m;i++){
            for(int j = 0;j < n;j++) {
                cover[i][j] = false;
            }
        }
        dfs(m, n, k, 0, 0, cover);
        int count = 0;
        for(int i = 0;i < m;i++) {
            for(int j = 0;j < n;j++) {
                if(cover[i][j]) count++;
            }
        }
        return count;
    }

    private void dfs(int m, int n, int k, int i, int j, boolean[][] cover) {
        cover[i][j] = true;
        int[][] direction = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for(int index = 0;index < direction.length;index++) {
            int newI = i + direction[index][0];
            int newJ = j + direction[index][1];
            if(newI >= 0 && newI < m && newJ >= 0 && newJ < n && !cover[newI][newJ]) {
                if(getUnitSum(newI, newJ) <= k) {
                    dfs(m, n, k, newI, newJ, cover);
                }
            }
        }
    }

    private int getUnitSum(int i, int j) {
        int result = 0;
        while(i > 0) {
            result += (i % 10);
            i /= 10;
        }
        while(j > 0) {
            result += (j % 10);
            j /= 10;
        }
        return result;
    }

    public static void main(String[] args) {
        Solution so = new Solution();
        System.out.println(so.movingCount(2,3,1));
        System.out.println(so.movingCount(3,1,0));
        System.out.println(so.movingCount(1,2,1));
    }
}