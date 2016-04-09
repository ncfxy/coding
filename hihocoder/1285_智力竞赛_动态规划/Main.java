import java.math.BigInteger;
import java.util.Arrays;
import java.util.Scanner;

/**
 * File Name: Main.java
 * Package Name: 
 * Description： TODO 
 *
 *   ver					date			author
 * ──────────────────────────────────
 *   1.0-SNAPSHOT			2016年3月30日			Administrator
 *
 * Copyright (c) 2016, alibaba-inc All Rights Reserved.
 */

/**
 * ClassName: Main<br/>
 * Description: TODO ADD Description
 *
 * @author Administrator
 * @version 1.0-SNAPSHOT
 * @Date 2016 2016年3月30日 下午2:39:34
 */

public class Main {
	
	public static int n,m,s,t;
	public static int inf = 0x7f7f7f7f;

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
        while(in.hasNext()) {
        	int q = in.nextInt();
        	for(int i = 0;i < q;i++){
        		dealWithProblem(in);
        	}
        }
	}
	
	public static void dealWithProblem(Scanner in){
		n = in.nextInt();
		m = in.nextInt();
		s = in.nextInt();
		t = in.nextInt();
		int[][] dp = new int[1005][1005];
		int[] A = new int[1005];
		for(int i = 1;i <= n;i++){
			A[i] = in.nextInt();
		}
		for(int i = 0;i < 1005;i++){
			Arrays.fill(dp[i], inf);
		}
		for(int i = 0;i <= m;i++){
			dp[i][0] = 0;
		}
		dpProcess(dp,A);
		int myMin = inf;
		for(int j = 0;j <=m;j++){
			if(dp[j][n] < myMin){
				myMin = dp[j][n];
			}
		}
		if(myMin > m)System.out.println("No");
		else System.out.println(myMin);
	}
	
	public static void dpProcess(int[][] dp, int[] A){
		for(int i = 1;i <= n;i++){
			int num = 0;
			if(A[i] %s == 0)num=A[i]/s;
			else num = A[i]/s + 1;
			for(int rightNumber = 0; rightNumber <= num;rightNumber++){
                int faultNumber = getCost(i,rightNumber,A);
                for(int j = 0;j <=m;j++){
                    if(j +rightNumber+faultNumber<=m){
                        dp[j +rightNumber+faultNumber][i] = Math.min(dp[j][i-1]+rightNumber,dp[j +rightNumber+faultNumber][i]);
                    }
                }
            }
		}
	}
	
	public static int getCost(int indexA,int rightNum,int[] A){
	    int result = (A[indexA] - s * rightNum);
	    if(result > 0){
	        if(result % t == 0){
	            return result/t;
	        }else{
	            return result/t + 1;
	        }
	    }else{
	        return 0;
	    }

	}
}
