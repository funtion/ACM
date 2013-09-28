import java.math.BigInteger;
import java.util.Scanner;


public class main {

	
	public static void main(String args[]) { 

        Scanner cin = new Scanner(System.in);  

        int a, b, t;
        
        t = cin.nextInt();
        for(int i=0;i<t;i++) {
        	
        	a = cin.nextInt();  
            b = cin.nextInt();
            BigInteger m = BigInteger.valueOf(a);
            BigInteger n = BigInteger.valueOf(b);
            BigInteger pa = m.pow(b-1);
            BigInteger gcd = pa.gcd(n);
            n = n.divide(gcd);
            pa = pa.divide(gcd);
            System.out.println(n.toString()+"/"+pa.toString()); 
        }
        
}  


}
