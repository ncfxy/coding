import java.util.Scanner;

public class Main {

    public static void main(String[] args){
        Main main = new Main();
        main.start();
    }

    public void start(){
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()){
            int N = cin.nextInt();
            if(N == 0)break;
            int current = 0, result = 0;
            int des;
            for(int i = 0;i < N;i++){
                des = cin.nextInt();
                if(des > current)result += (des - current) * 6;
                else if(des < current) result += (current - des) * 4;
                result += 5;
                current = des;
            }
            System.out.println(result);
        }
    }
}
