import java.awt.*;

class CanvasClass extends Canvas{ // Canvas parent class
public void paint(Graphics g){ // Graphics g()paint meth(defined alredy)
int circleX = 50, circleY = 50;
int lineStartX = 200, lineStartY = 50;
int pointX = 350, pointY = 50;
int rectX = 50, rectY = 200;
int triangleX = 400, triangleY = 200;

g.setColor(Color.BLUE); // g.setColor(Color.BLUE RED BLACK YELLOW GREEN MAGENTA);
g.drawOval(circleX, circleY, 100, 100);

g.setColor(Color.BLACK);
g.drawLine(lineStartX, lineStartY, lineStartX + 100, lineStartY + 100);

g.setColor(Color.YELLOW);
g.fillOval(pointX, pointY, 5, 5);

g.setColor(Color.RED);
g.fillOval(pointX + 10, pointY, 5, 5);

g.setColor(Color.GREEN);
g.drawRect(rectX, rectY, 100, 100);

g.setColor(Color.MAGENTA);

int[] xPoints = {triangleX, triangleX + 50, triangleX - 50};
int[] yPoints = {triangleY, triangleY + 100, triangleY + 100};
g.drawPolygon(xPoints, yPoints, 3);

}
}

public class AWT4_graphic {
public static void main(String[] args){
Frame frame = new Frame("AWT Drawing box windows(frame)"); // Frame f = new Frame("title is it");
CanvasClass canv1 = new CanvasClass(); // Canvas extened class instance alloc
canv1.setSize(1000, 900); // Canvas::setSize(1000, 1000);

frame.add(canv1); // frame(Frame new).add(object one);
frame.setSize(800, 600);
frame.setVisible(true);

frame.addWindowListener(new java.awt.event.WindowAdapter() { // frame.addWindowListener(new java.awt.event.WindowAdapter(){ public void windowClosing(java.awt.event.WindowEvent e){ }});
public void windowClosing(java.awt.event.WindowEvent e){
	System.exit(1);
}
});
}
}
 
