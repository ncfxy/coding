/**
 * File Name: Solution.java
 * Package Name: com.ncfxy.haha
 * Description： TODO 
 *
 *   ver					date			author
 * ──────────────────────────────────
 *   1.0-SNAPSHOT			2016年4月5日			Administrator
 *
 * Copyright (c) 2016, ncfxy All Rights Reserved.
 */

package com.ncfxy.haha;

import java.util.Arrays;

/**
 * ClassName: Solution<br/>
 * Description: TODO ADD Description
 *
 * @author Administrator
 * @version 1.0-SNAPSHOT
 * @Date 2016 2016年4月5日 下午10:52:33
 */
public class Solution {

	public int maxProfit(int[] prices) {
		int length = prices.length;
		if (length < 1)
			return 0;
		int dp[][] = new int[4][length];
		Arrays.fill(dp[0], Integer.MAX_VALUE);
		Arrays.fill(dp[1], Integer.MIN_VALUE);
		Arrays.fill(dp[2], Integer.MIN_VALUE);
		Arrays.fill(dp[3], Integer.MIN_VALUE);
		for (int i = 0; i < length; i++) {
			if (i == 0){
				dp[0][i] = prices[i];
				dp[1][i] = prices[i] - dp[0][i];
				dp[2][i] = dp[1][i] - prices[i];
				dp[3][i] = prices[i] + dp[2][i];
			}
			else {
				dp[0][i] = Math.min(dp[0][i - 1], prices[i]);

				dp[1][i] = Math.max(dp[1][i - 1], prices[i] - dp[0][i]);
				dp[2][i] = Math.max(dp[2][i - 1], dp[1][i] - prices[i]);
				dp[3][i] = Math.max(dp[3][i - 1], prices[i] + dp[2][i]);
			}
		}
		return dp[3][length - 1];
	}

	public static void main(String[] args) {
		Solution so = new Solution();
		int prices[] = { 1, 4, 2 };
		System.out.println(so.maxProfit(prices));
	}

}
