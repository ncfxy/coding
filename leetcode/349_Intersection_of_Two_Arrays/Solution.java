import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

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

	public int[] intersection(int[] nums1, int[] nums2) {
		Set<Integer> set = new HashSet<Integer>();
		Set<Integer> result = new HashSet<Integer>();
		for(int n:nums1){
			set.add(n);
		}
		for(int x:nums2){
			if(set.contains(x)){
				result.add(x);
			}
		}
		int[] r = new int[result.size()];
		int index = 0;
		for (int i : result) {
			r[index++] = i;
		}
		return r;
	}

	public static void main(String[] args) {
		Solution s = new Solution();
		int[] nums = { 0, 1, 0, 3, 12 };
	}
}
