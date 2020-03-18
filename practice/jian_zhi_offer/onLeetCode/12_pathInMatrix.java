class Solution {
    public boolean exist(char[][] board, String word) {
        if(word == null || word.length() == 0) {
            return true;
        }
        if(board == null || board.length == 0 || board[0].length == 0) {
            return false;
        }
        boolean[][] cover = new boolean[board.length][board[0].length];
        for(int i = 0;i < board.length;i++) {
            for(int j = 0;j < board[0].length;j++) {
                    cover[i][j] = false;
            }
        }
        boolean result = false;
        for(int i = 0;i < board.length && !result;i++) {
            for(int j = 0;j < board[0].length && !result;j++) {
                if(board[i][j] == word.charAt(0)) {
                    cover[i][j] = true;
                    result = dfs(board, word, cover, 1, i, j);
                    cover[i][j] = false;
                }
            }
        }
        return result;
    }

    private boolean dfs(char[][] board, String word, boolean[][] cover, int currentWordIndex, int i, int j) {
        int[][] direction = {{1, 0}, {-1,0}, {0 ,1}, {0,-1}};
        if(currentWordIndex >= word.length()) {
            return true;
        }
        boolean result = false;
        for(int index = 0;index < direction.length && !result;index++) {
            int newI = i + direction[index][0];
            int newJ = j + direction[index][1];
            if(newI >= 0 && newI < board.length && newJ >= 0 && newJ < board[0].length){
                if(word.charAt(currentWordIndex) == board[newI][newJ] && !cover[newI][newJ]) {
                    cover[newI][newJ] = true;
                    result = result | dfs(board, word, cover, currentWordIndex + 1, newI, newJ);
                    cover[newI][newJ] = false;
                }
            }
        }
        return result;
    }

    public static void main(String[] args) {
        Solution so = new Solution();
        char[][] board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
        String word = "ABCCED";
        System.out.println(so.exist(board, word));

    }
}