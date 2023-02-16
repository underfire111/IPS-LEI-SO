package srcs;

import java.util.Random;

public class MyThread extends Thread {

	public static volatile boolean running = true;

	@Override
	public void run() {
		
		Knapsack lbk = null;
		Random rand = new Random();
		
		int alpha = 0;
		int counter = 0;

		while (MyThread.running) {
			
			counter++;
			lbk = BeamSearch.lowerBound();
			
			alpha = rand.nextInt(Info.size / 2) + 1;
			
			BeamSearch.search(alpha, lbk);
			
			if (lbk.getCurPrice() > Result.getBestSolution().getCurPrice()) {
				Result.updateResult(lbk, System.nanoTime(), counter);
			}

		} System.exit(0);

	}

}
