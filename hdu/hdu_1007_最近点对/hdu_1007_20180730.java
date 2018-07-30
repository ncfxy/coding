import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

class Node{
    double x;
    double y;
}

class SortByX implements Comparator<Node> {

    @Override
    public int compare(Node o1, Node o2) {
        if(o1.x < o2.x){
            return -1;
        }else if(o1.x > o2.x) {
            return 1;
        }
        return 0;
    }
}

class SortByY implements Comparator<Node> {

    @Override
    public int compare(Node o1, Node o2) {
        if(o1.y < o2.y){
            return -1;
        }else if(o1.y > o2.y) {
            return 1;
        }
        return 0;
    }
}

public class Main {
    public Node nd[] = new Node[100005];
    public static void main(String[] args){
        Main main = new Main();
        main.start();
    }

    public void start() {
        Scanner cin = new Scanner(System.in);
        for(int i = 0;i < 100005;i++){
            nd[i] = new Node();
        }
        while(cin.hasNext()){
            int N = cin.nextInt();
            if(N == 0){
                break;
            }
            for(int i = 0;i < N;i++){
                nd[i].x = cin.nextDouble();
                nd[i].y = cin.nextDouble();
            }
            Arrays.sort(nd, 0, N - 1, new SortByX());
            System.out.println(formatDouble(find(0, N-1)/2));
        }
    }

    public double find(int left, int right) {
        if(right - left == 1) {
            return getDistance(left, right);
        }
        int mid = (left + right) / 2;
        double res = Math.min(find(left, mid), find(mid, right));
        Node tmpNode = new Node();
        tmpNode.x = nd[mid].x;
        tmpNode.y = nd[mid].y;
        Arrays.sort(nd, left, right, new SortByY());
        for(int i = left;i < right;i++) {
            if(nd[i].x - tmpNode.x < res && tmpNode.x - nd[i].x < res) {
                for(int j = i + 1;j <= right;j++){
                    if(nd[j].y - nd[i].y > res){
                        break;
                    }
                    res = Math.min(res, getDistance(i,j));
                }
            }
        }

        return res;
    }

    public double getDistance(int a, int b){
        return Math.sqrt((nd[a].x - nd[b].x) * (nd[a].x - nd[b].x) + (nd[a].y - nd[b].y) * (nd[a].y - nd[b].y));
    }

    public String formatDouble (double num) {
        return String.format("%.2f", num);
    }
}
