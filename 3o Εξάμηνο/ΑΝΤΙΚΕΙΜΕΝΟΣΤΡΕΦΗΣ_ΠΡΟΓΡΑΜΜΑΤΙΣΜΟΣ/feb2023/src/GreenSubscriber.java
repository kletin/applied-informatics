
public class GreenSubscriber extends Subscriber {
	
	private static double averageKilovatores;
	private String location;
	private Solarpanel solarpanel;
	
	public GreenSubscriber(String surname, double averageKilovatores, String location) {
		super(surname, averageKilovatores);
		this.location = location;
		// TODO Auto-generated constructor stub
	}

}
