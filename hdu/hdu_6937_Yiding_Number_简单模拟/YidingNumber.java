import java.util.*;

public class YidingNumber
{
    public static void main(String args[])
    {
        YidingNumber m = new YidingNumber();
        m.init();
    }

    public void init() {
        Queue<Integer> q = new LinkedList<Integer>();
        Map<Integer, Boolean> m = new HashMap<Integer, Boolean>();
        q.add(1);
        m.put(1, true);
        while(!q.isEmpty()) {
            Integer value = q.remove();
            m.put(value, true);
            int a[] = {1,2,3,4};
            a[0] = 5 * value + 13;
            a[1] = 13 * value + 5;
            a[2] = 5 * value - 13;
            a[3] = 13 * value - 5;
            for (int i = 0; i < 4;i++) {
                Boolean b = m.get(a[i]);
                if (a[i] > 0 && a[i] <= 1000000 && b == null) {
                    q.add(a[i]);
                    m.put(a[i], true);
                }
            }
        }

        Scanner cin = new Scanner(System.in);
        while(cin.hasNextInt()) {
            int t = cin.nextInt();
            for (int i = 0;i < t; i++) {
                int n = cin.nextInt();
                Boolean b = m.get(n);
                if (b != null) {
                    System.out.println("Yes");
                } else {
                    System.out.println("No");
                }
            }
        }
    }
}