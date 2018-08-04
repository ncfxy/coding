import java.util.Scanner;

public class Main {

    double allDayTime = 12 * 60 * 60;
    double eps = 0.0000001;
    // speed 
    double speedH = 1.0 / 120;
    double speedM = 1.0 / 10;
    double speedS = 6.0;
    // related speed
    double speedHM = speedM - speedH;
    double speedHS = speedS - speedH;
    double speedMS = speedS - speedM;
    // related period
    double periodHM = 360.0 / speedHM;
    double periodHS = 360.0 / speedHS;
    double periodMS = 360.0 / speedMS;
    
    public static void main(String[] args){
        Main main = new Main();
        main.start();
    }

    public void start(){
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()){
            double N = cin.nextDouble();
            if(N < 0){
                break;
            }
            solve(N);
        }
    }

    public void solve(double degree){
        double start[] = new double[3];
        double end[] = new double[3];
        start[0] = degree / speedHM;
        start[1] = degree / speedHS;
        start[2] = degree / speedMS;
        end[0] = (360 - degree) / speedHM;
        end[1] = (360 - degree) / speedHS;
        end[2] = (360 - degree) / speedMS;

        double i[] = new double[3];
        double j[] = new double[3];
        double sum = 0.0;
        for(i[0] = start[0], j[0] = end[0]; j[0] < allDayTime + eps;i[0] += periodHM, j[0] += periodHM){
            for(i[1] = start[1], j[1] = end[1]; j[1] < allDayTime + eps;i[1] += periodHS, j[1] += periodHS){
                if (i[1] > j[0])
                    break;
                if (j[1] < i[0])
                    continue;
                for(i[2] = start[2], j[2] = end[2]; j[2] < allDayTime + eps;i[2] += periodMS, j[2] += periodMS){
                    if (i[2] > j[1])
                        break;
                    if (j[2] < i[1])
                        continue;
                    double from = Math.max(Math.max(i[0], i[1]), i[2]);
                    double to = Math.min(Math.min(j[0], j[1]), j[2]);
                    sum += Math.max(0.0, to - from);
                }
            }
        }
        System.out.println(formatDouble(sum * 100.0 / allDayTime));
    }

    public String formatDouble(double num) {
        return String.format("%.3f", num);
    }


}