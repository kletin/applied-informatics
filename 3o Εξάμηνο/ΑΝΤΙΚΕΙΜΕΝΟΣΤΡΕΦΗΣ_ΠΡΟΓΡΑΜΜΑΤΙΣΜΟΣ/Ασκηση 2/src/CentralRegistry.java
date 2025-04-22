import java.util.ArrayList;

public class CentralRegistry {
    private static ArrayList<Airport> airports;
    private static ArrayList<Flight> flights;

   /**
	 * Constructs a CentralRegistry object with initialized lists for airports and flights.
	 * This constructor is responsible for initializing the central registry.
	 * @param name    The name of the airport.
	 * @param code    The code identifying the airport.
	 * @param city    The city where the airport is located.
	 * @param country The country where the airport is located.
	 */
	    
    public CentralRegistry() {
        CentralRegistry.airports = new ArrayList<>();
        CentralRegistry.flights = new ArrayList<>();
    }
    
    /**
	 * <This method adds a flight to the flights List>
	 * 
	 * @param <flight> - <the name of the flight >
	 */
    
    
    public static void addFlight(Flight aFlight) {
    	if (flights == null) {
            flights = new ArrayList<>();
        }
        flights.add(aFlight);

        
        Airport airportA = aFlight.getAirportA();
        Airport airportB = aFlight.getAirportB();

        airportA.addConnectedAirport(airportB);
        airportB.addConnectedAirport(airportA);

        String airline = aFlight.getAirline();
        airportA.addΑirline(airline);
        airportB.addΑirline(airline);
    }
    
    /**
   	 * <This method adds an airport to the aiports List>
   	 * 
   	 * @param <anAirport> - <the name of the airport >
   	 */
    
    public static void addAirport(Airport anAirport) {
    		
    	if (airports == null) {
                airports = new ArrayList<>();
            }
            airports.add(anAirport);
            }
  
    /**
   	 * <This method returns the largest hub >
   	 * 
   	 * @param <largestHub> - <the name of the airport >
   	 */
	
    
    
	public static Airport getLargestHub() {
		
        if (airports.isEmpty()) {
            return null; 
        }

        Airport largestHub = airports.get(0);
		for(Airport airport : airports ) {
			if (airport.getConnectedAirports().size() > largestHub.getConnectedAirports().size()) {
                largestHub = airport;
            }
        }
		return largestHub;
	}  
	  /**
   	 * <This method returns the longestFlight >
   	 * 
   	 * @return <longestFlight> - <the airports of the flight >
   	 */
	
	public static Flight getLongestFlight() {
		
        if (flights.isEmpty()) {
            return null; // Επιστρέφει null αν δεν υπάρχουν συνδέσεις
        }
		Flight longestFlight = flights.get(0); 
		for(Flight flight : flights ) {
			if (flight.getDurationMinutes() >longestFlight.getDurationMinutes()) {
				longestFlight = flight;
			}
		}
		return longestFlight;
	}
	
	
	
		
	}
