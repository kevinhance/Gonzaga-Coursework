import java.util.Scanner;

public class PlayGame {
	public static void main(String[] args) {
		int numOfPlayers;
		int currentTurn = 0, currentRound = 0, currentPlayer = 0;
		String userIn = "nnnnn";
		Hand[] players;
		Scanner sysIn = new Scanner(System.in);
		System.out.println("Welcome to Space Race!");
		System.out.print("Please enter the desired amount of players: ");
		numOfPlayers = sysIn.nextInt();
		sysIn = new Scanner(System.in);
		System.out.println("Starting game with " + numOfPlayers + " players");
		players = initPlayers(numOfPlayers);
		while(currentRound < 10) {
			System.out.println("\n\nRound " + (currentRound + 1));
			while(currentPlayer < (numOfPlayers)) {
				System.out.println("Player " + (currentPlayer + 1) + "'s turn");
				while(currentTurn < 3 && !userIn.equals("yyyyy")) {
					for(int i = 0; i < 5; i++) {	//Reroll the dice they decided to change
						if(userIn.charAt(i) == 'n')
							players[currentPlayer].reroll(i);
					}
				
					System.out.println("Your roll: " + players[currentPlayer]);
					System.out.print("Select resources to keep (y/n): ");
					userIn = sysIn.nextLine();
					currentTurn++;
				}
				players[currentPlayer].sort();
				System.out.println("Your final hand is: " + players[currentPlayer].toString());
			}
		}
		sysIn.close();
	}
	
	public static Hand[] initPlayers(int numOfPlayers) {
		Hand[] players = new Hand[numOfPlayers];
		for(int i = 0; i < numOfPlayers; i++) {
			players[i] = new Hand();
		}
		return players;
	}
}
