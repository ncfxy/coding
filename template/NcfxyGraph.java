import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Stack;

// 使用邻接链表实现的图
public class NcfxyGraph implements NcfxyGraphInterface {

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
