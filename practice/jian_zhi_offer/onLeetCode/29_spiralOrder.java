class Solution extends Thread{
    public int[] spiralOrder(int[][] matrix) {
        if(matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            int[] result = new int[0];
            return result;
        }
        int row = matrix.length;
        int column = matrix[0].length;
        int[] result = new int[row * column];
        int index = 0;
        int startPoint = 0;
        int times = (Math.min(row, column) + 1) / 2;
        while(startPoint < times) {
            for(int i = startPoint;i < column - startPoint;i++) {
                result[index++] = matrix[startPoint][i];
            }
            for(int i = startPoint + 1;i < row - startPoint;i++) {
                result[index++] = matrix[i][column - startPoint - 1];
            }
            for(int i = column - startPoint - 2;i >= startPoint && row-startPoint-1 > startPoint;i--) {
                result[index++] = matrix[row - startPoint - 1][i];
            }
            for(int i = row - startPoint - 2;i > startPoint && startPoint < column - startPoint - 1;i--) {
                result[index++] = matrix[i][startPoint];
            }
            startPoint++;
        }
        return result;
    }

    public void run() {
        int[][] matrix = {
                {1,2,3},
                {4,5,6},
                {7,8,9}
        };
        int[] result = this.spiralOrder(matrix);
        for(int i = 0;i < result.length;i++) {
            System.out.println(result[i]);
        }
        int[][] matrix2 = {
                {1,2,3,4},
                {5,6,7,8},
                {9,10,11,12}
        };
        int[] result2 = this.spiralOrder(matrix2);
        for(int i = 0;i < result2.length;i++) {
            System.out.println(result2[i]);
        }
    }

    public static void main(String[] args) {
        new Solution().start();
    }
}