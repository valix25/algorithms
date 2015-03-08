
import java.util.Scanner;

public class TestUnionFindAlgorithms {

	private static Scanner reading;

	public static void main(String[] args){
		
		reading = new Scanner(System.in);
		int N = reading.nextInt();
		WQUPC uf = new WQUPC(N);
		while(reading.hasNext())
		{
		    int p = reading.nextInt();
		    int q = reading.nextInt();
	            if(!uf.connected(p, q))
			{
				uf.union(p, q);
				System.out.println(p+" "+q);
			}
			uf.print_array(N);
		}
	}
	
}
