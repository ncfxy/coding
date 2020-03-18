public class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) {
        val = x;
    }

    static void preTraverse(TreeNode root) {
        if(root == null) {
            return;
        }
        System.out.print(root.val + ",");
        preTraverse(root.left);
        preTraverse(root.right);
    }

    static void midTraverse(TreeNode root) {
        if(root == null) {
            return;
        }
        midTraverse(root.left);
        System.out.print(root.val + ",");
        midTraverse(root.right);
    }

    static void postTraverse(TreeNode root) {
        if(root == null) {
            return;
        }
        postTraverse(root.left);
        postTraverse(root.right);
        System.out.print(root.val + ",");
    }

}