package srcs;

import java.util.ArrayList;
import java.util.Collections;

public class Main {
	
	// [order] [path] [threads] [time] [iterations]
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

		for (int i = 0; i < Info.threads; i++) {

			MyThread thread = new MyThread();
			thread.start();

		}

		long begin = System.nanoTime();
		long now;

		do {
			now = System.nanoTime();
		} while ((int)((now - begin) / 1000000000) < Info.time); // american billion
		
		MyThread.running = false;
		
		System.out.println("Best result: " + Result.getBestSolution().getCurPrice()
		+ " | " + Result.getBestSolution().getCurWeight());
		System.out.println();
		
		System.out.println("Time: " + (begin - Result.getTime()));

		System.exit(1);

	}

}
