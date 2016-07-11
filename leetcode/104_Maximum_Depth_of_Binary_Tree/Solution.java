/**
 * File Name: Solution.java
 * Package Name: 
 * Description： TODO 
 *
 *   ver					date			author
 * ──────────────────────────────────
 *   1.0-SNAPSHOT			2016年7月11日			ncfxy
 *
 * Copyright (c) 2016, ncfxy All Rights Reserved.
 */

/**
 * ClassName: Solution<br/>
 * Description: TODO ADD Description
 *
 * @author ncfxy
 * @version 1.0-SNAPSHOT
 * @Date 2016 2016年7月11日 下午8:19:10
 */
public class Solution {

//	public class TreeNode {
//		int val;
//		TreeNode left;
//		TreeNode right;
//
//		TreeNode(int x) {
//			val = x;
//		}
//	}

	public int maxDepth(TreeNode root) {
		if(root == null)return 0;
		int max = 1;
		if(root.left != null){
			int a = maxDepth(root.left) + 1;
			max = Math.max(max, a);
		}
		if(root.right != null){
			int a = maxDepth(root.right) + 1;
			max = Math.max(max, a);
		}
		return max;
	}

	public static void main(String[] args) {
		Solution s = new Solution();
		TreeNode root = new TreeNode(1);
		root.left = new TreeNode(1);
		root.right = new TreeNode(2);
		root.left.left = new TreeNode(3);
		System.out.println(s.maxDepth(root));
	}
}


