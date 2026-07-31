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
		if(prices.length < 1)return 0;
		int ans = 0,tmp = prices[0];
		for(int i = 1;i < prices.length;i++){
			if(prices[i] > prices[i-1]){
				
			}else{
				ans += prices[i-1] - tmp;
				tmp = prices[i];
			}
		}
		ans += prices[prices.length-1] - tmp;
		return ans;
	}

	public static void main(String[] args) {
		Solution so = new Solution();
		int prices[] = { 1, 4, 2 ,5};
		System.out.println(so.maxProfit(prices));
	}

}
