import java.util.Scanner;

public class Hdu1040 {
    public static void main(String args[])
    {
        Hdu1040 m = new Hdu1040();
        m.solve1();
    }

    public void solve1() {
        Scanner cin = new Scanner(System.in);
        while(cin.hasNextInt()) {
            int t = cin.nextInt();
            for (int i = 0;i < t;i++) {
                int count = cin.nextInt();
                NcfxyHeap heap = new NcfxyHeap();
                for (int j = 0;j < count;j++) {
                    int num = cin.nextInt();
                    heap.push(num);
                }
                while(heap.getLen() > 0) {
                    int num = heap.pop();
                    System.out.print(num);
                    if (heap.getLen() > 0) {
                        System.out.print(" ");
                    }
                }
                System.out.println();
            }
        }
    }

    public class NcfxyHeap {
        private int MAX = 20000;
        private int []num = new int[MAX];
        private int len;
    
        public NcfxyHeap() {
            len = 0;
        }
    
        public void up(int idx) {
            int tmp = num[idx];
            while(idx >= 2 && num[idx>>1] > tmp) {
                num[idx] = num[idx>>1];
                idx >>= 1;
            }
            num[idx] = tmp;
        }
    
        public void down(int idx) {
            int downIdx = idx << 1, tmp = num[idx];
            while(downIdx <= len) {
                if (downIdx + 1 <= len && num[downIdx] > num[downIdx + 1])downIdx++;
                if (tmp <= num[downIdx])break;
                num[idx] = num[downIdx];
                idx = downIdx;
                downIdx <<= 1;
            }
            num[idx] = tmp;
        }
    
        public void push(int n) {
            num[++len] = n;
            up(len);
        }
    
        public int pop() {
            int tmp = num[1];
            if (len == 0) return -1;
            num[1] = num[len--];
            if (len == 0) return tmp;
            down(1);
            return tmp; 
        }
    
        public int getLen() {
            return len;
        }
    }
}

