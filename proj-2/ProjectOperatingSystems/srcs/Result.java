package srcs;

public class Result {
	
	private static volatile Knapsack bestSolution = BeamSearch.lowerBound();
	private static volatile long time = 0;
	private static volatile long iterations = 0;

	public static synchronized void updateResult(Knapsack k, long time, long iterations) {

		if(k.getCurPrice() > bestSolution.getCurPrice()) {
			Result.iterations = iterations;
			Result.bestSolution = k;
			Result.time = time;
		}

	}

	public static Knapsack getBestSolution() {
		return bestSolution;
	}

	public static long getIterations() {
		return iterations;
	}

	public static long getTime() {
		return time;
	}

}
