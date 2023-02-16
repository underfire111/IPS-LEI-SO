package srcs;

import java.util.List;

public class Info {
	
	public static volatile List<Item> items;
	public static volatile int size;
	public static volatile int bestResult;
	public static volatile String path;
	public static volatile int order;
	public static volatile int time;
	public static volatile int threads;	
	public static volatile int iterations;

	public static void init() {

		Info.order = 0;
		Info.path = "./data/ex25.txt";
		Info.threads = 3;
		Info.time = 10;
		Info.iterations = 10000;
	
	}

}
