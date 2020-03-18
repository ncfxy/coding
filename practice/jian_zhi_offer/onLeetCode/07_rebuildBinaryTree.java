class Solution {
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        if(preorder.length == 0) {
            return null;
        }
        Map<Integer, Integer> inorderMap = new HashMap();
        for(int i = 0;i < inorder.length;i++) {
            inorderMap.put(inorder[i], i);
        }
        TreeNode root = buildTreeInner(preorder, inorder, 0, 0, preorder.length, inorderMap);
        return root;
    }

    private TreeNode buildTreeInner(int[] preorder, int[] inorder, int preorderStart, int inorderStart, int length, Map<Integer, Integer> inorderMap) {
        if(length < 1) {
            return null;
        }
        if(length == 1) {
            return new TreeNode(preorder[preorderStart]);
        }
        int inorderLocation = inorderMap.get(preorder[preorderStart]);
        int leftLength = inorderLocation - inorderStart;
        int rightLength = length - leftLength - 1;
        TreeNode root = new TreeNode(preorder[preorderStart]);
        root.left = buildTreeInner(preorder, inorder, preorderStart + 1, inorderStart, leftLength, inorderMap);
        root.right = buildTreeInner(preorder, inorder, preorderStart + leftLength + 1, inorderStart + leftLength + 1, rightLength, inorderMap);
        return root;
    }

    public static void main(String[] args) {
        Solution so = new Solution();
        int[] preorder = {3, 9, 20, 15, 7};
        int[] inorder = {9, 3, 15, 20, 7};
        TreeNode node = so.buildTree(preorder, inorder);
        TreeNode.preTraverse(node);
        System.out.println();
        TreeNode.midTraverse(node);
        System.out.println();
    }

}