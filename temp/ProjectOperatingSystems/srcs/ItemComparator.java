package srcs;

import java.util.Comparator;

public class ItemComparator implements Comparator<Item> {

	@Override
	public int compare(Item o1, Item o2) {
		
		double v1 = (double)(o1.getPrice() / o1.getWeight());
		double v2 = (double)(o2.getPrice() / o2.getWeight());

		if (v1 > v2) {
			return -1;
		} else if (v1 < v2) {
			return 1;
		} return 0;

	}

}
