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

	public TreeNode invertTree(TreeNode root) {
		if(root == null)return root;
		TreeNode tmp = root.left;
		root.left = root.right;
		root.right = tmp;
		if(root.left != null){
			invertTree(root.left);
		}
		if(root.right != null){
			invertTree(root.right);
		}
		return root;
	}

	public static void main(String[] args) {
		Solution s = new Solution();
		TreeNode root = new TreeNode(1);
		root.left = new TreeNode(1);
		root.right = new TreeNode(2);
		root.left.left = new TreeNode(3);
		System.out.println(s.invertTree(root));
	}
}
