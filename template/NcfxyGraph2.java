import java.util.*;

// 使用链式前向星进行存图
public class NcfxyGraph2 implements NcfxyGraphInterface {
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

    public NcfxyGraph2() {
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
