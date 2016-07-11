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
	public String reverseString(String s) {
		StringBuffer buffer = new StringBuffer();
		for(int i = 0;i < s.length();i++){
			buffer.insert(0, s.charAt(i));
		}
		return buffer.toString();
	}

	public static void main(String[] args) {
		String str = "hello";
		Solution s = new Solution();
		System.out.println(s.reverseString(str));
		
	}
}
