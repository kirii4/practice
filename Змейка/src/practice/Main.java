package practice;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class Main extends JPanel implements ActionListener{
    public static JFrame jFrame;
    public static final int SCALE = 48;
    public static final int WIDTH = 20;
    public static final int HEIGHT = 20;
    public static  int speed = 15;
    public int rX = (int)(Math.random() * WIDTH - 1);
    public int rY = (int)(Math.random()  * HEIGHT - 1);
    
    static Snake s = new Snake(5,5,5,6);
    Apple a = new Apple(rX, rY);

    Timer timer = new Timer(1000 / speed, this);

    public Main(){
        timer.start();
        addKeyListener(new Keyboard());
        setFocusable(true);
    }

    public void paint(Graphics g){

        g.setColor(Color.darkGray); //background
        g.fillRect(0,0,SCALE * WIDTH, SCALE * HEIGHT);

//        for(int x = 0; x < SCALE * WIDTH; x += SCALE){ //вертикальные линии
//            g.setColor(Color.black);
//            g.drawLine(0,x,SCALE * WIDTH, x);
//        }

//        for(int y = 0; y < SCALE * HEIGHT; y += SCALE){ //горизонтальные линии
//            g.setColor(Color.black);
//            g.drawLine(y,0,y, HEIGHT * SCALE);
//        }
        g.setColor(Color.RED); // apple
        g.fillOval(a.aX * SCALE + 5, a.aY * SCALE + 5, SCALE - 8, SCALE - 8);

        for(int i = 1; i < s.len; i++){
            g.setColor(Color.GREEN);
            g.fillOval(s.sX[i] * SCALE + 3, s.sY[i] * SCALE + 3, SCALE - 6, SCALE - 6);
            g.setColor(Color.PINK);
            g.fillOval(s.sX[0] * SCALE + 3, s.sY[0] * SCALE + 3, SCALE - 6, SCALE - 6);
        } //snake

        g.setColor(Color.white); //Score game
        String str = String.valueOf("Score: " + s.len);
        Font f = new Font("TIMES NEW ROMAN", Font.BOLD, 17);
        g.setFont(f);
        g.drawString(str, SCALE * WIDTH - 70,17);
    }

    public static void main(String[] args) {
        jFrame = new JFrame("Змейка");
        jFrame.setSize(WIDTH * SCALE + 18, HEIGHT * SCALE + 8);

        jFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        jFrame.setResizable(false);
        jFrame.setLocationRelativeTo(null);

        jFrame.add(new Main());
        jFrame.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        s.move();
        repaint();
        if (s.sX[0] == a.aX && s.sY[0] == a.aY) {
            s.len++;
            a.rdPoint(); // новая позиция яблока
            speed += 10;
        }
        for(int i = 1; i < s.len; i++){
            if (s.sX[i] == a.aX && s.sY[i] == a.aY) a.rdPoint();
            if (s.sX[0] == s.sX[i] && s.sY[0] == s.sY[i]) {
                timer.stop();
                int menu = JOptionPane.showConfirmDialog(null, "Вы проиграли, продолжить? ");
                if (menu == 0){    //YES
                    jFrame.setVisible(false);
                    s.len = 2;
                    s.direction = 0;
                    a.rdPoint();
                    jFrame.setVisible(true);
                    timer.start();
                }
                else{ //NO, other
                    System.exit(0);
                }
            }
        } //Lose
        if (s.len == 33) {
            timer.stop();
            JOptionPane.showMessageDialog(null, "Вы выйграли!!!");
            System.exit(0);
        } //Win
    }

    public class Keyboard extends KeyAdapter{
        public void keyPressed(KeyEvent event){
            int key = event.getKeyCode();
            // up - 0, down - 2, left - 3, right - 1
            if ((key == KeyEvent.VK_UP || key == KeyEvent.VK_W) &&
                    (s.direction != 2)) s.direction = 0;
            if ((key == KeyEvent.VK_DOWN || key == KeyEvent.VK_S) &&
                    (s.direction != 0)) s.direction = 2;
            if ((key == KeyEvent.VK_LEFT || key == KeyEvent.VK_A) &&
                    (s.direction != 1)) s.direction = 3;
            if ((key == KeyEvent.VK_RIGHT || key == KeyEvent.VK_D) &&
                    (s.direction != 3)) s.direction = 1;
        }
    }
}