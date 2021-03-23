class Solution extends Thread{
    public boolean isSymmetric(TreeNode root) {
        return root == null || isSymmetricForTwoSub(root.left, root.right);
    }

    public boolean isSymmetricForTwoSub(TreeNode left, TreeNode right) {
        if(left == null && right == null) return true;
        if(left == null || right == null || left.val != right.val)return false;
        return isSymmetricForTwoSub(left.left, right.right) && isSymmetricForTwoSub(left.right, right.left);
    }

    public void run() {
    }

    public static void main(String[] args) {
        new Solution().start();
    }
}