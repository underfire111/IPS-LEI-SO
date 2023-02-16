package srcs;

import java.io.BufferedReader;

public class FileReader {
	
	public static void importData() {
		
		BufferedReader reader = null;
		String buffer = null;

		try {
		
			int counter = -1;
			int numberOfItems = 0;
			
			reader = new BufferedReader(new java.io.FileReader(Info.path));

			while ((buffer = reader.readLine()) != null) {
				
				counter++;
				if (counter == 0) { 
					numberOfItems = Integer.parseInt(buffer);
				} else if (counter == 1) {
					Knapsack.maxWeight = Integer.parseInt(buffer);
				} else {
					
					for (int i = 0; i < numberOfItems; i++) {
						
						String [] tokens = buffer.split(" ", 2);
			
						int price = Integer.parseInt(tokens[0]);
						int weight = Integer.parseInt(tokens[1]);
						Item item = new Item(price, weight);
						
						Info.items.add(item);
						
						buffer = reader.readLine();

					} Info.bestResult = Integer.parseInt(buffer);
					
				} 
				
			}

		} catch (Exception e) {

			System.err.println("Error: " + e.getMessage());
		
		} finally {

			try {
				reader.close();
			} catch (Exception e) {
				System.err.println(e.getMessage());
			}

		}

	}
}