package srcs;

public class Knapsack {
	
	public static int maxWeight;
	private Byte [] solution;
	private int curPrice;
	private int curWeight;

	public Knapsack() {
		this.solution = new Byte[Info.size];
		setFalse();

		this.curPrice = 0;
		this.curWeight = 0;

	}

	public Knapsack(Byte [] solution, int price, int weight) {
		this.solution = solution;
		this.curPrice = price;
		this.curWeight = weight;
	}

	private void setFalse() {
		solution[0] = -1;
		for (int i = 1; i < Info.size; i++) {
			solution[i] = 0;
		}
	}

	public int getCurPrice() {
		return curPrice;
	}

	public void addCurPrice(int curPrice) {
		this.curPrice += curPrice;
	}

	public int getCurWeight() {
		return curWeight;
	}

	public void addCurWeight(int curWeight) {
		this.curWeight += curWeight;
	}

	public Byte[] getSolution() {
		return solution;
	}

	public void setNewSolution(Byte[] solution, int price, int weight) {
		this.solution = solution;
		this.curPrice = price;
		this.curWeight = weight;
	}

	public Knapsack clone() {

		Byte [] cloneSolution = new Byte[Info.size];

		for (int i = 0; i < Info.size; i++) {
			cloneSolution[i] = this.solution[i];
		}

		Knapsack clone = new Knapsack(cloneSolution, this.curPrice, this.curWeight);

		return clone;

	}
	

}
