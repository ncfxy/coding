/**
 * File Name: Hdu1102.java
 * Package Name: com.ncfxy.MyAlgorithm
 * Description： TODO 
 *
 *   ver					date			author
 * ──────────────────────────────────
 *   1.0-SNAPSHOT			2016年4月6日			Administrator
 *
 * Copyright (c) 2016, ncfxy All Rights Reserved.
*/

/**
 * ClassName: Main<br/>
 * Description:	 TODO ADD Description
 *
 * @author   Administrator
 * @version  1.0-SNAPSHOT
 * @Date	 2016	2016年4月6日		下午1:42:56
 */
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Stack;



public class Hdu1102 {

	public static void main(String[] args) {
		Hdu1102 m = new Hdu1102();
		m.solve1();
	}

	public void solve1() {
		DirectedGraph g = new DirectedGraph();
		Scanner cin = new Scanner(System.in);
		int[][] dis = new int[105][105];
		while (cin.hasNext()) {
			int n = cin.nextInt();
			g.addPoint(n);
			for(int i = 1;i <= n;i++ ){
				for(int j = 1;j <= n;j++){
					dis[i][j] = cin.nextInt();
				}
			}
			int q = cin.nextInt();
			for(int i = 0;i < q;i++){
				int a = cin.nextInt();
				int b = cin.nextInt();
				dis[a][b] = 0;
				dis[b][a] = 0;
			}
			for(int i = 1;i <= n;i++ ){
				for(int j = 1;j <= n;j++){
					g.addEdge(i-1, j-1, dis[i][j]);
				}
			}
			System.out.println(g.Prim());
		}
	}

	public class GraphPoint {
		private int index;
		private List<Integer> NextPoint = new ArrayList<Integer>();
		private List<Integer> edgeValue = new ArrayList<Integer>();

		public int getIndex() {
			return index;
		}

		public void setIndex(int index) {
			this.index = index;
		}

		public List<Integer> getNextPoint() {
			return NextPoint;
		}

		public void setNextPoint(List nextPoint) {
			NextPoint = nextPoint;
		}

		public List<Integer> getEdgeValue() {
			return edgeValue;
		}

		public void setEdgeValue(List edgeValue) {
			this.edgeValue = edgeValue;
		}
	}

	public class DirectedGraph {

		List<GraphPoint> pointList = new ArrayList<GraphPoint>();

		public void addPoint(int totalPointNumber) {
			pointList.clear();
			for (int i = 0; i < totalPointNumber; i++) {
				GraphPoint graphPoint = new GraphPoint();
				graphPoint.setIndex(i);
				pointList.add(graphPoint);
			}
		}

		public void addEdge(int from, int to, int value) {
			if (from > pointList.size() || to > pointList.size()) {
				return;
			}
			(pointList.get(from)).getNextPoint().add(to);
			(pointList.get(from)).getEdgeValue().add(value);
		}


		/**
		 * getStrongGraphByTarjan: 实现强连通分量的Tarjan算法，并返回强连通分量的列表
		 *
		 * @return
		 * @since  MyAlgorithm　Ver 1.0-SNAPSHOT
		 */
		public List<List<Integer>> getStrongGraphByTarjan() {
			int dfn[] = new int[pointList.size()];
			int low[] = new int[pointList.size()];
			int color[] = new int[pointList.size()];
			List<List<Integer>> result = new ArrayList<List<Integer>>();
			Stack<Integer> stack = new Stack<Integer>();
			int index = 0;
			Arrays.fill(color, 0);
			for (int i = 0; i < pointList.size(); i++) {
				if (color[i] == 0) {
					color[i] = 1;
					stack.push(i);
					tarjanDfs(i, dfn, low, color, result, index, stack);
				}
			}
			return result;
		}

		private void tarjanDfs(int pointNumber, int[] dfn, int[] low, int[] color,
							   List<List<Integer>> result, int index, Stack<Integer> stack) {
			dfn[pointNumber] = low[pointNumber] = index++;
			for (int i = 0; i < pointList.get(pointNumber).getNextPoint().size(); i++) {
				int endPointNumber = pointList.get(pointNumber).getNextPoint().get(i);
				if (color[endPointNumber] == 0) {
					color[endPointNumber] = 1;
					stack.push(endPointNumber);
					tarjanDfs(endPointNumber, dfn, low, color, result, index, stack);

				}
				low[pointNumber] = Math.min(low[pointNumber], low[endPointNumber]);
			}
			color[pointNumber] = 2;
			if (low[pointNumber] == dfn[pointNumber]) {
				List<Integer> list = new ArrayList<Integer>();
				while (true) {
					int point = stack.pop();
					if (point == pointNumber) {
						list.add(point);
						break;
					} else {
						list.add(point);
					}
				}
				result.add(list);
			}
		}

		public int Prim(){
			int result = 0;
			int[] dist = new int[pointList.size()];
			int[] cover = new int[pointList.size()];
			int s = 0, temp = 0, flag= 0;
			Arrays.fill(cover, 0);
			Arrays.fill(dist, Integer.MAX_VALUE);
			dist[0] = 0;

			for(int i = 0;i < pointList.size();i++){
				temp = Integer.MAX_VALUE;
				for(int j = 0;j < pointList.size();j++){
					if(cover[j] == 0 && dist[j] < temp){
						temp = dist[j];
						flag = j;
					}
				}
				if(temp == Integer.MAX_VALUE)return -1;
				cover[flag] = 1;
				result += dist[flag];
				GraphPoint point = pointList.get(flag);
				for(int x = 0;x < point.getNextPoint().size();x++){
					int y = point.getNextPoint().get(x);
					int value = point.getEdgeValue().get(x);
					if(cover[y] == 0 && dist[y] > value){
						dist[y] = value;
					}
				}
			}
			return result;
		}

	}

}