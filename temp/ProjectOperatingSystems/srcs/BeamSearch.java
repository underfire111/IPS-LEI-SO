package srcs;

import java.util.ArrayList;
import java.util.Random;

/**
 * Beam Search
 */
public class BeamSearch {

	// beam search algorithm
	public static void search(int alpha, Knapsack lowerBound) {

		ArrayList<Knapsack> solutions = initSolution();
		int level = 0;

		while (!solutions.isEmpty() && level < Info.size) {
			
			if (MyThread.running == false) {
				return;
			}

			solutions = getChilds(solutions, level++);

			int size = solutions.size();

			int i = -1;
			while (++i < size) {

				Knapsack k = solutions.get(i);

				int upperBound = upperBound(k, level);
				if (upperBound >= lowerBound.getCurPrice()) {
					if (k.getCurPrice() > lowerBound.getCurPrice()) {
						lowerBound.setNewSolution(k.getSolution(), k.getCurPrice(), k.getCurWeight());
					}
				} else {
					solutions.remove(i--);
					size--;
				}

			} solutions = selectSolution(alpha, solutions);

		}

	}

	// calculates the lower bound.
	public static Knapsack lowerBound() {

		int c;
		Knapsack k = new Knapsack();

		for (c = 0; c < Info.size; c++) {

			Item item = Info.items.get(c);

			k.getSolution()[c] = 1;

			if (c < Info.size - 1) {
				k.getSolution()[c + 1] = -1;
			}

			k.addCurWeight(item.getWeight());
			k.addCurPrice(item.getPrice());

			if (k.getCurWeight() > Knapsack.maxWeight) {

				k.addCurWeight(-item.getWeight());
				k.addCurPrice(-item.getPrice());

				k.getSolution()[c] = 0;
				break;

			}

		} return k;

	}

	// calculate the upper bound of an incomplete solution.
	private static int upperBound(Knapsack k, int level) {

		int c; // index of the first items that cannot be inserted.
		Knapsack k1 = k.clone();

		Byte[] seq = k1.getSolution(); // solution.

		for (c = level; c < Info.size - 1; c++) {

			if (seq[c] == 0 || seq[c] == 1) { continue ; }

			Item item = Info.items.get(c);

			seq[c] = 1;

			if (c < Info.size - 1) {
				seq[c + 1] = -1;
			}

			k1.addCurWeight(item.getWeight());
			k1.addCurPrice(item.getPrice());

			if (k1.getCurWeight() > Knapsack.maxWeight) {

				k1.addCurWeight(-item.getWeight());
				k1.addCurPrice(-item.getPrice());

				k1.getSolution()[c] = 0;
				break;

			}

		}
		
		if (c >= Info.size - 1) { return k1.getCurPrice(); }

		// weight of all items not selected.
		int w = Knapsack.maxWeight - k1.getCurWeight();

		// .out.printf("price: %s weight: %s\n", k.getCurPrice(), k.getCurWeight());

		int a = k1.getCurPrice() + (int) (w * Info.items.get(c + 1).getPrice()
				/ Info.items.get(c + 1).getWeight());

		int b = k1.getCurPrice() + (int) (Info.items.get(c).getPrice()
				- ((Info.items.get(c).getWeight() - w) * Info.items.get(c - 1).getPrice()
				/ Info.items.get(c - 1).getWeight()));

		return Math.max(a, b);
		
	}

	// get all possible solutions left.
	private static ArrayList<Knapsack> getChilds(ArrayList<Knapsack> list, int level) {

		if (level > Info.size) {
			return null;
		}

		ArrayList<Knapsack> newList = new ArrayList<>();

		for (Knapsack k : list) {

			Byte[] original = k.getSolution();
			Byte[] clone1 = original.clone();

			int price = Info.items.get(level).getPrice();
			int weight = Info.items.get(level).getWeight();

			// swap the leftmost -1 to 0 and 1
			original[level] = 0;
			clone1[level] = 1;

			// set -1 at the next level
			if (level < Info.size - 1) {
				original[level + 1] = -1;
				clone1[level + 1] = -1;
			}

			Knapsack k1 = new Knapsack(clone1, k.getCurPrice() + price, k.getCurWeight() + weight);

			newList.add(k);
			if (k1.getCurWeight() <= Knapsack.maxWeight) {
				newList.add(k1);
			}

		} return newList;

	}

	// select alpha solutions from a list of solutions.
	private static ArrayList<Knapsack> selectSolution(int alpha, ArrayList<Knapsack> solutions) {

		int size = solutions.size();

		if (size < alpha) {
			return solutions;
		}

		Random rand = new Random();
		ArrayList<Knapsack> keepSolution = new ArrayList<>();

		for (int i = 0; i < alpha; i++) {
			if (size == 0) {
				break;
			} keepSolution.add(solutions.remove(rand.nextInt(size--)));
		} return keepSolution;

	}

	// creates an initial solution where with no items pre-selected.
	private static ArrayList<Knapsack> initSolution() {

		ArrayList<Knapsack> solutions = new ArrayList<>();
		Knapsack k = new Knapsack();

		solutions.add(k);

		return solutions;

	}

}
