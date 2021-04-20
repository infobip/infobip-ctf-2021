import java.util.Random;
import java.util.Scanner;
import java.lang.System;
import java.lang.Integer;

public class TheGame {

	private static final String FLAG = "ibctf{4lways_use-s3cure_prngs}";
	private static final int WIN_COUNT = 100;

	public static void main(String... args) {
		Random random = new Random();
		Scanner scanner = new Scanner(System.in);
		int counter = 0;
		String guess = "";
		
		System.out.println("Welcome! Welcome! To the one and only GAME!");
		System.out.println("Use x to exit");
		System.out.println("I am thinking of one number, can you guess what it is?");
		while(true) {
			try {
				int think = random.nextInt();
				guess = scanner.next();
				
				int guessNum = Integer.parseInt(guess);
				if(guessNum == think) {
					System.out.println("WOW! That's correct!");
					counter++;
				} else {
					System.out.printf("Nope! I was thinking of %d\n", think);
				}
				
				if(counter >= WIN_COUNT) {
					System.out.printf("Congratulations! The flag is %s\n", FLAG);
					break;
				}
				System.out.println("OK, new number, try the next again.");
			} catch(NumberFormatException nfe) {
				if(guess.charAt(0) == 'x') {
					System.out.println("Oh! Exit request!");
					break;
				} else {
					System.out.println("Not a number!");
				}
			} catch(Exception e) {
				System.out.println("Oops! Something went really wrong!");
			}
		}
	}
}
