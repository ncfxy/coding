class Solution extends Thread{

    public int[] levelOrder(TreeNode root) {
        if(root == null) {
            int[] result = new int[0];
            return result;
        }
        Deque<TreeNode> queue = new LinkedList<>();
        List<Integer> result = new LinkedList<>();
        queue.offer(root);
        while(!queue.isEmpty()) {
            TreeNode first = queue.poll();
            result.add(first.val);
            if(first.left != null) queue.offer(first.left);
            if(first.right != null) queue.offer(first.right);
        }
        int[] resultArray = new int[result.size()];
        int index = 0;
        Iterator<Integer> iterator = result.iterator();
        while(iterator.hasNext()) {
            resultArray[index++] = iterator.next();
        }
        return resultArray;
    }

    public void run() {
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(9);
        root.right = new TreeNode(20);
        root.right.left = new TreeNode(15);
        root.right.right = new TreeNode(7);
        int[] result = this.levelOrder(root);
        for(int i = 0;i < result.length;i++) {
            System.out.println(result[i]);
        }

    }

    public static void main(String[] args) {
        new Solution().start();
    }
}