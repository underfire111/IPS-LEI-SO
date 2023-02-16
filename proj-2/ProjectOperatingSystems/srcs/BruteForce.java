package srcs;

import java.util.ArrayList;
import java.util.Collections;

public class BruteForce {
	
	public static int search() {
	 
		int[][] dp = new int[Info.size + 1][Knapsack.maxWeight + 1];

		for (int i = 1; i <= Info.size; i++) {
			
			for (int j = 1; j <= Knapsack.maxWeight; j++) {

				Item item = Info.items.get(i - 1);
			
				if (item.getWeight() > j) { dp[i][j] = dp[i - 1][j]; }
				else {
					dp[i][j] = Math.max(dp[i - 1][j], dp[i - 1][j - item.getWeight()] + item.getPrice());
				}
			
			}

		} return dp[Info.size][Knapsack.maxWeight];
	}

	public static void main(String[] args) {

		try {

			Info.order = Integer.parseInt(args[0]);
			Info.path = "./data/" + args[1] + ".txt";
			Info.threads = Integer.parseInt(args[2]);
			Info.time = Integer.parseInt(args[3]);
			Info.iterations = Integer.parseInt(args[4]);
			
		} catch (Exception e) {
			Info.init();
		}
		
		Info.items = new ArrayList<>();

		FileReader.importData();
		Collections.sort(Info.items, new ItemComparator());

		if (Info.items.isEmpty()) { System.exit(1); }

		Info.size = Info.items.size();

		System.out.println(BruteForce.search());

		System.exit(0);
	}

	

}
