import java.awt.Dimension;
import java.awt.Toolkit;
import java.swing.*;

public class BuildPhase implements JFrame{
	
	Hand[] players;
	int numPlayers;
	
	public static void main(String[] args){
		BuildPhase b = new BuildPhase(Hand );
	}
	
	public BuildPhase(Hand[] initPlayers){
		players = initPlayers;
		numPlayers = players.length;
		
		JPanel panel = new JPanel();
		
		
		
	}
	
	public void playBuild(Hand[] hArr){ // this is basically the main method of BuildPhase
		for(int i = 0; i < 10; i++){//loop for 10 turns
			for(int j = 0; j < 4; j++){
				// roll 3 times
				boolean continueRolling;
				for(int k = 0; k < 3 && continueRolling; k++){
					//if the player doesn't want to roll again, set continueRolling to false
					rollResources(players[j]);
				}
				printBuildOptions(players[j]);
				
			}
		}
	}
	
	private void rollResources(Hand h){ // 
		for(int i = 0; i < 5; i++){
			h.playerResources[i].randomResource();
		}
	}
	
	private void swingInit(){
		this.setSize(400); // parameter
		this.setLocationRelativeTo(null);
		this.setVisible(true);
		
		Toolkit tk = Toolkit.getDefaultToolkit;
		Dimension dim = tk.getScreenSize();
		
		int xPos = (dim.width/2) - (this.getWidth()/2);
		int yPos = (dim.height/2) - (this.getHeight()/2);
		
		this.setLocation(xPos, yPos);
		this.setResizable(false);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		this.setTitle("SPACE RACE: Build Phase");
	}
	
	private void printBuildOptions(Hand h){
		if(canBuildCockpit(h)){
			//cockpit can be built (UI stuff)
			if(!h.checkPartBuilt(6)){
				System.out.println("Cockpit Mk1 can be built");
			} else if(!h.checkPartBuilt(7)){
				System.out.println("Cockpit Mk2 can be built");
			} else if(!h.checkPartBuilt(8)){
				System.out.println("Cockpit Mk3 can be built");
			}
		} if(canBuildThruster(h)){
			//Thruster can be built (UI stuff)
			if(!h.checkPartBuilt(0)){
				System.out.println("Thruster Mk1 can be built");
			} else if(!h.checkPartBuilt(1)){
				System.out.println("Thruster Mk2 can be built");
			} else if(!h.checkPartBuilt(2)){
				System.out.println("Thruster Mk3 can be built");
			}
		} if(canBuildFuelReserves(h)){
			//fuel reserve can be built (UI stuff)
			if(!h.checkPartBuilt(3)){
				System.out.println("Fuel Reserves Mk1 can be built");
			} else if(!h.checkPartBuilt(4)){
				System.out.println("Fuel Reserves Mk2 can be built");
			} else if(!h.checkPartBuilt(5)){
				System.out.println("Fuel Reserves Mk3 can be built");
			}
		} if(canAddCrewMembers(h)){
			//1 crew member can be added (UI stuff)
			if(!h.checkCrewFull()){
				System.out.println("1 crew member can be added");
			}
		} if(canAddFuel(h)){
			int amountOfFuel = calcFuelQuantity(h);
			//<amountOfFuel> units of fuel can be added (UI stuff)
			System.out.println(amountOfFuel + " units of fuel can be added");
		}
	}
	
	private void buildThruster(Hand h){
		if(canBuildThruster(h)){
			if(!h.checkPartBuilt(0)){
				h.buildPart(0);
			} else if(!h.checkPartBuilt(1)){
				h.buildPart(1);
			} else if(!h.checkPartBuilt(2)){
				h.buildPart(2);
			}
		}
	}
	
	private void buildFuelReserves(Hand h){
		if(canBuildFuelReserves(h)){
			//fuel reserve can be built (UI stuff)
			if(!h.checkPartBuilt(3)){
				h.buildPart(3);
			} else if(!h.checkPartBuilt(4)){
				h.buildPart(4);
			} else if(!h.checkPartBuilt(5)){
				h.buildPart(5);
			}
		}
	}
	
	private void buildCockpit(Hand h){
		if(canBuildCockpit(h)){
			//cockpit can be built (UI stuff)
			if(!h.checkPartBuilt(6)){
				h.buildPart(6);
			} else if(!h.checkPartBuilt(7)){
				h.buildPart(7);
			} else if(!h.checkPartBuilt(8)){
				h.buildPart(8);
			}
		}
	}
	
	private void addCrewMember(Hand h){
		if(canAddCrewMembers(h)){
			//1 crew member can be added (UI stuff)
			if(!h.checkCrewFull()){
				h.addCommodity(0);
			}
		}
	}
	
	private void addFuel(Hand h){
		int amountOfFuel = calcFuelQuantity(h);
		for(int i = 0; i < amountOfFuel; i++){
			h.addCommodity(1);
		}
	}
	
	private boolean canBuildCockpit(Hand h){
		return (h.numberOfHullParts() >= 1 &&
				h.numberOfElectronics() >= 1 &&
				h.numberOfGlass() >= 1 &&
				h.numberOfCrewMembers() >= 1);
	}
	
	private boolean canBuildThruster(Hand h){
		return (h.numberOfHullParts() >= 1 &&
				h.numberOfElectronics() >= 1 &&
				h.numberOfFuel() >= 2);
	}
	
	private boolean canBuildFuelReserves(Hand h){
		return (h.numberOfHullParts() >= 1 &&
				h.numberOfElectronics() >= 1 &&
				h.numberOfFuel() >= 2);
	}
	
	private boolean canAddFuel(Hand h){
		return (h.numberOfFuel() >= 3 && h.checkPartBuilt(3));
	}
	
	private boolean canAddCrewMembers(Hand h){
		return (h.numberOfCrewMembers >= 3);
	}
	
	private int calcFuelQuantity(Hand h){
		if(h.numberOfFuel() < 3)
			return 0;
		if(h.numberOfFuel() == 3)
			return 1;
		else if(h.numberOfFuel() == 4)
			return 2;
		else if(h.numberOfFuel() == 5)
			return 3;
	}
	
}
