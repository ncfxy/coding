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
	public int add(int a, int b) {
		if (a == 0)
			return b;
		if (b == 0)
			return a;
		while (b != 0) {
			int tmp = (a & b);
			a = a ^ b;
			b = tmp << 1;
		}
		return a;
	}

	public int getSubtract(int a, int b) {
		while (b != 0) {
			int borrow = (~a) & b;
			a = a ^ b;
			b = borrow << 1;
		}
		return a;
	}

	public int getSum(int a, int b) {
		if (a >= 0 && b >= 0) {
			return add(a, b);
		} else if (a < 0 && b < 0) {
			return -add(-a, -b);
		} else if (a < 0) {
			return getSubtract(b, -a);
		}
		return getSubtract(a, -b);
	}

	public static void main(String[] args) {
		int a = 12;
		int b = 22;
		Solution s = new Solution();
		System.out.println(s.getSubtract(a, b));
		a = -1;
		System.out.println(~1);
		System.out.println(~2);
	}
}
