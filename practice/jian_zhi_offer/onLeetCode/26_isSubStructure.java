class Solution extends Thread{
    public boolean isSubStructure(TreeNode A, TreeNode B) {
        if(A == null || B == null) {
            return false;
        }
        boolean result = false;
        if(A.val == B.val) {
            result = result || isSame(A, B);
        }
        result = result || isSubStructure(A.left, B) || isSubStructure(A.right, B);
        return result;
    }

    public boolean isSame(TreeNode A, TreeNode B) {
        if(B == null) {
            return true;
        }
        if(A == null) {
            return false;
        }
        return A.val == B.val && isSame(A.left, B.left) && isSame(A.right, B.right);
    }

    public void run() {
        TreeNode A = new TreeNode(3);
        A.left = new TreeNode(4);
        A.right = new TreeNode(5);
        A.left.left = new TreeNode(1);
        A.left.right = new TreeNode(2);
        TreeNode B = new TreeNode(4);
        B.left = new TreeNode(1);
        System.out.println(isSubStructure(A, B));
    }

    public static void main(String[] args) {
        new Solution().start();
    }
}