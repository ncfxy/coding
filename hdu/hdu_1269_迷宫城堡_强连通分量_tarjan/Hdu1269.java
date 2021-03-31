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

public class Hdu1269 {

	public static void main(String[] args) {
		Hdu1269 m = new Hdu1269();
		m.solve1();
	}

	public void solve1() {
		DirectedGraph g = new DirectedGraph();
		Scanner cin = new Scanner(System.in);
		while (cin.hasNext()) {
			int n = cin.nextInt();
			int m = cin.nextInt();
			if (n == m && m == 0) {
				break;
			}
			g.addPoint(n);
			for (int i = 0; i < m; i++) {
				int a = cin.nextInt();
				int b = cin.nextInt();
				g.addEdge(a - 1, b - 1, 0);
			}
			// System.out.println(g.getStrongGraphByTarjan());
			if (g.getStrongGraphByTarjan().size() > 1) {
				System.out.println("No");
			} else {
				System.out.println("Yes");
			}
		}
	}

	static class GraphPoint {
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

	static class DirectedGraph {

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
	}

}