class UThread extends Thread{
  public void run(int i){ 
    System.out.println("my thread 1: arg1(" + i + ") only\n");
  }
}

public class javaMainThread_test{
  public static void main(String[] args)
  {
    UThread myth = new UThread();

    System.out.print("[Threads]\n"); 
    myth.run(7);
    myth.run(3);
    myth.run(2);
    myth.run(1);
    myth.run(0);
    myth.run(4);
  }
}
