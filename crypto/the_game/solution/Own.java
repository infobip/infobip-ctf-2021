import java.util.*;
import java.io.*;
import java.net.*;


/**
 * Reference: https://raw.githubusercontent.com/BaiqingL/PredictJavaNextInt/master/predict.java
 */
public class Own {
	private Socket clientSocket;
    private PrintWriter out;
    private BufferedReader in;
 
    public void startConnection(String ip, int port) throws Exception {
        clientSocket = new Socket(ip, port);
        out = new PrintWriter(clientSocket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
    }
 
    public String sendMessage(String msg) throws Exception {
        out.println(msg);
        String resp = in.readLine();
        return resp;
    }
 
    public void stopConnection() throws Exception {
        in.close();
        out.close();
        clientSocket.close();
    }

    private static int calculated(long seed) throws Exception {
        //32 bit MIN MAX value
        int bits = 32;
        long seed2 = (seed * 25214903917L + 11) & 281474976710655L;
        return (int)(seed2 >>> (48 - bits));
    }
    
    public void own() throws Exception {
    	startConnection("192.168.57.1", 9000);
    	System.out.println(in.readLine());
    	System.out.println(in.readLine());
    	System.out.println(in.readLine());
    	System.out.println(sendMessage("0"));
    	System.out.println(in.readLine());
    	System.out.println(sendMessage("0"));
    	System.out.println(in.readLine());
        long seed = 0;
        Scanner z = new Scanner(System.in);
        System.out.println("Enter a randomly generated number (random.nexInt() method) by java:");
        long target1 = z.nextLong();
        System.out.println("Enter the SECOND randomly generated number:");
        long target2 = z.nextLong();
        //Brute forcing begins
        for (int i = 0; i < 65536; i++) {
            seed = target1 * 65536 + i;
            if (calculated(seed) == target2) {
                System.out.println("Seed found: " + seed);
                break;
            }
        }

        //Setting the exact seed to replicate the original run of generating numbers
        Random random = new Random((seed ^ 25214903917L) & 281474976710655L);
	    int result2 = random.nextInt();
        for (int i = 0; i < 100; i++) {
		    result2 = random.nextInt();
		    System.out.println(String.format("My random: %d", result2));
			System.out.println(sendMessage(String.valueOf(result2)));
			System.out.println(in.readLine());
	    }
    }

    public static void main(String[] args) throws Exception {
    	Own o = new Own();
    	o.own();
    }
}

