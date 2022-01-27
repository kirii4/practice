package practice;

import static practice.Main.*;

public class Apple {
    public int aX;
    public int aY;

    public Apple(int x, int y){
        aX = x;
        aY = y;
    }

    public void rdPoint(){
        aX = (int)(Math.random() * WIDTH - 1);
        aY = (int)(Math.random() * HEIGHT - 1);
    }
}
