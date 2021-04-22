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
		DirectedGraph2 g = new DirectedGraph2();
		Scanner cin = new Scanner(System.in);
		while (cin.hasNext()) {
			int test = cin.nextInt();
			System.out.println(test ^ 1);
			if (test != -100) {
				continue;
			}
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



	// 使用邻接链表实现的图
	public class DirectedGraph {

		public class Edge {
			private int to;
			private int value;
			public Edge(int to, int value) {
				this.to = to;
				this.value = value;
			}
		}

		public class GraphPoint {
			private List<Edge> edges = new ArrayList<>();
		}

		List<GraphPoint> pointList = new ArrayList<GraphPoint>();

		public void addPoint(int totalPointNumber) {
			pointList.clear();
			for (int i = 0; i < totalPointNumber; i++) {
				GraphPoint graphPoint = new GraphPoint();
				pointList.add(graphPoint);
			}
		}

		public void addEdge(int from, int to, int value) {
			if (from > pointList.size() || to > pointList.size()) {
				return;
			}
			pointList.get(from).edges.add(new Edge(to, value));
		}


		/**
		 * getStrongGraphByTarjan: 实现强连通分量的Tarjan算法，并返回强连通分量的列表
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
			for (int i = 0; i < pointList.get(pointNumber).edges.size(); i++) {
				int endPointNumber = pointList.get(pointNumber).edges.get(i).to;
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

	// 使用链式前向星进行存图
	public class DirectedGraph2 {
		public class Edge {
			Integer to, value;
			Edge next;
			public Edge(int to, int value) {
				this.to = to;
				this.value = value;
				this.next = null;
			}
		}

		private List<Edge> edgeList;
		private List<Edge> head;

		public DirectedGraph2() {
			this.edgeList = new ArrayList<>();
			this.head = new ArrayList<>();
		}

		public void addPoint(int totalPointNumber) {
			this.head = new ArrayList<>(totalPointNumber);
			for (int i = 0; i < totalPointNumber; i++) {
				this.head.add(null);
			}
		}

		public void addEdge(int from, int to, int value) {
			Edge edge = new Edge(to, value);
			edgeList.add(edge);
			edge.next = head.get(from);
			head.set(from, edge);
		}

		/**
		 * getStrongGraphByTarjan: 实现强连通分量的Tarjan算法，并返回强连通分量的列表
		 */
		public List<List<Integer>> getStrongGraphByTarjan() {
			int dfn[] = new int[head.size()];
			int low[] = new int[head.size()];
			int color[] = new int[head.size()];
			List<List<Integer>> result = new ArrayList<List<Integer>>();
			Stack<Integer> stack = new Stack<Integer>();
			int index = 0;
			Arrays.fill(color, 0);
			for (int i = 0; i < head.size(); i++) {
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
			for (Edge edge = head.get(pointNumber); edge != null; edge = edge.next) {
				int endPointNumber = edge.to;
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