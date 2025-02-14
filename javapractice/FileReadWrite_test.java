/*
   FileReadWrite_test.java
   
   Author: KyongJu, Jung
   Up_Date: 2025.2.14 (Fri) in south korea
*/

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileReadWrite_test{
  public static void main(String[] args){

    String readFileName = new String("readexam1.txt");
    String writeFileName = new String("writeexam2.txt");
    String line = new String("");

    try(BufferedReader br = new BufferedReader(new FileReader(readFileName))){
      while((line = br.readLine()) != null){
        System.out.println(line);
      }
    }
    catch(IOException ioe)
    {
      System.out.println(ioe.getMessage());
    }

    try(BufferedWriter bw = new BufferedWriter(new FileWriter(writeFileName, true))){
      bw.write("foo\n");
    }
    catch(IOException ioe2)
    {
      System.out.println(ioe2.getMessage());
    }

  }
}
