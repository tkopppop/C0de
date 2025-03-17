/*
   Filename: RSAJava.java
   Author: x90c(tf8) as KyongJu_Jung

   Description:
   This is the RSA Encrypt/Decrypt

   - BITS(2048 Bit Key using Encryption) from 512...(bit)
   - DOFI(doFinal) do final method support only byte series(bytes). -- and no more important args. only one arg is on,.
   

   *sigh* It's a my basic code to java programming language. is java good? x (by me)
   *sigh* passwd supportng pki's private style keyring is next types.
   
*/

import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.util.Arrays;
import javax.crypto.Cipher;

public class RSAjava {
  public static void main(String[] args) {

    try {
       
      KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance("RSA");
      keyPairGenerator.initialize(2048); /* BITS */
      KeyPair keyPair = keyPairGenerator.generateKeyPair();

      PublicKey publicKey = keyPair.getPublic();
      PrivateKey privateKey = keyPair.getPrivate();
      String pl = "Hello rsa encryption text is it";
      System.out.println("Original texts: " + pl);

      Cipher cipher = Cipher.getInstance("RSA");
      cipher.init(Cipher.ENCRYPT_MODE, publicKey); /* INIT */
      byte[] encryptedBytes = cipher.doFinal(pl.getBytes());
      System.out.println("Encrypted: " + Arrays.toString(encryptedBytes));

      cipher.init(Cipher.DECRYPT_MODE, privateKey);
      byte[] decryptedBytes = cipher.doFinal(encryptedBytes); /* DOFI */
      String decryptedText = new String(decryptedBytes);
      System.out.println("Dec: " + decryptedText);
       
    } catch(Exception e) {

       e.printStackTrace();
 
    } finally {

    }
  }

}

/*
   END END END END END END END END END END(except toda erika)
*/
