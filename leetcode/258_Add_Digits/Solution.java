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
	public int addDigits(int num) {
		if(num == 0)return num;
		else return (num % 9) == 0 ? 9 : (num % 9);
	}

	public static void main(String[] args) {
		Solution s = new Solution();
		System.out.println(s.addDigits(38));
	}
}
