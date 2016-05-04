/**
 * File Name: Main.java
 * Package Name: com.ncfxy.MyAlgorithm
 * Description： TODO 
 *
 *   ver					date			author
 * ──────────────────────────────────
 *   1.0-SNAPSHOT			2016年4月6日			Administrator
 *
 * Copyright (c) 2016, ncfxy All Rights Reserved.
*/

package com.ncfxy.MyAlgorithm;

import java.util.Scanner;

/**
 * ClassName: Main<br/>
 * Description:	 TODO ADD Description
 *
 * @author   Administrator
 * @version  1.0-SNAPSHOT
 * @Date	 2016	2016年4月6日		下午1:42:56
 */


public class Main {

	public static void main(String[] args) {

		Scanner cin = new Scanner(System.in);
		while(cin.hasNext()){
			int t = cin.nextInt();
			for(int i = 0;i < t;i++){
				System.out.println(sol(cin));
			}
		}

	}
	
	public static int sol(Scanner cin){
		int n = cin.nextInt();
		int p = cin.nextInt();
		int w = cin.nextInt();
		int h = cin.nextInt();
		int a[] = new int[n];
		for(int i = 0;i < n;i++){
			a[i] = cin.nextInt();
		}
		int left = 1;
		int right = Math.min(w, h);
		while(left <= right){
			int mid = (left + right) >> 1;
			int result = getResult(a,n,w,h,mid);
			if(result <= p){
				left = mid + 1;
			}else {
				right = mid -1;
			}
		}
		return right;
	}
	
	public static int  getResult(int[] a, int n,int  w, int h,int size){
		int lineNumber = 0;
		for(int i = 0;i < a.length;i++){
			int everyLineChar = w / size;
			if(a[i] % everyLineChar == 0)
				lineNumber += a[i] / everyLineChar;
			else
				lineNumber += a[i] / everyLineChar + 1;
		}
		int everyPageLine = h / size;
		if(lineNumber % everyPageLine == 0){
			return lineNumber / everyPageLine;
		}else{
			return lineNumber / everyPageLine + 1;
		}
	}

}