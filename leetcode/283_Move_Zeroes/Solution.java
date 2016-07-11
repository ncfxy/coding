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

	public void moveZeroes(int[] nums) {
		int index = 0;
		for(int i = 0;i < nums.length;i++){
			if(nums[i] != 0){
				int tmp = nums[index];
				nums[index] = nums[i];
				nums[i] = tmp;
				index++;
			}
		}
	}

	public static void main(String[] args) {
		Solution s = new Solution();
		int[] nums = {0,1,0,3,12};
		s.moveZeroes(nums);
		for(int i = 0;i < nums.length;i++){
			System.out.println(nums[i]);
		}
	}
}
