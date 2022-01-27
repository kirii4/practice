package practice;

import static practice.Main.*;

public class Snake {
    public int len = 2;
    public int direction = 3;
    public int[] sX = new int [WIDTH * SCALE];
    public int[] sY = new int [HEIGHT * SCALE];

    public Snake(int x1, int y1, int x2, int y2){
        sX[0] = x1;
        sX[1] = y1;
        sY[0] = x2;
        sY[1] = y2;
    }

    public void move(){

        for (int i = len; i > 0; i--){
            sX[i] = sX[i - 1];
            sY[i] = sY[i - 1];
        }

        if (direction == 0) sY[0]--;        //up
        if (direction == 1) sX[0]++;        //right
        if (direction == 2) sY[0]++;        //down
        if (direction == 3) sX[0]--;        //left

        if (sY[0] >  HEIGHT - 2) sY[0] = 0;
        if (sY[0] <  0) sY[0] = HEIGHT - 2;
        if (sX[0] > WIDTH - 1) sX[0] = 0;
        if (sX[0] < 0) sX[0] = WIDTH - 1;
    }
}
