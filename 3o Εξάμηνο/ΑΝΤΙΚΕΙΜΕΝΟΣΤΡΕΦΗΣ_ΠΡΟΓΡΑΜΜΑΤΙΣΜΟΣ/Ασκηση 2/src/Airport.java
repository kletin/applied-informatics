import java.util.Set;
import java.util.ArrayList;
import java.util.HashSet;

public class Airport {
	private static final int MAX_DEPTH = 1;
	private String name;
	private String code;
	private String city;
	private String country;
	private ArrayList<String> airlines;
	private ArrayList<Airport> connectedAirports;
	
	/**
	 * Constructs an Airport object with the specified parameters.
	 *
	 * @param name    The name of the airport.
	 * @param code    The code identifying the airport.
	 * @param city    The city where the airport is located.
	 * @param country The country where the airport is located.
	 */
	
	
	public Airport(String name, String code, String city, String country) {
		this.name = name;
		this.code = code;
		this.city = city;
		this.country = country;
		this.airlines = new ArrayList<>();
		this.connectedAirports = new ArrayList<>();
	}

	/**
	 * <This method returns the connected airports. >
	 * 
	 * @return <connectedAirports>
	 */

	public ArrayList<Airport> getConnectedAirports() {
		return connectedAirports;
	}

	/**
	 * <This method returns the name of the airport>
	 * 
	 * @return name
	 */

	public String getName() {
		return name;
	}

	/**
	 * <This method returns the city of the airport>
	 * 
	 * @return city
	 */

	public String getCity() {
		return city;
	}

	/**
	 * <This method returns the name of the country>
	 * 
	 * @return country
	 */

	public String getCountry() {
		return country;
	}

	/**
	 * <This method returns the airlines.>
	 * 
	 * @return airlines
	 */

	public ArrayList<String> getAirlines() {
		return airlines;
	}

	/**
	 * <This method returns the code of the airport.>
	 * 
	 * @return code
	 */

	public String getCode() {
		return code;
	}

	/**
	 * <This method adds a list of airlines to the airlines list.>
	 * @param <airline> - <the list of the airlines>
	 * 
	 */
	public void addAirlines(ArrayList<String> airline) {
		airlines.addAll(airline);
	}

	/**
	 * <This method adds one airline to the airport object >
	 * 
	 * @param <airline> - < The name of the airline to be added>
	 *
	 */
	
	public void addΑirline(String airline) {
		airlines.add(airline);
	}

	/**
	 * <This method adds a connected airport to the connectedAirports list>
	 * 
	 * @param <airport> - <the name of the airport>
	 */
	
	public void addConnectedAirport(Airport airport) {
		connectedAirports.add(airport);
	}

	/**
	 * <This methods checks if another airport is directly connected to this one>
	 * 
	 * @param <airport> - <The name of the other airport>
	
     * @return <true> if there is an direct connection, false otherwise.
	 */
	public Boolean isDirectlyConnectedTo(Airport anAirport) {
		return connectedAirports.contains(anAirport);

	}

	/**
	 * <This methods checks if another airport is indirectly connected to this one>
	 * 
	 * @param <airport> - <the name of the other airport>
     * @return <true> if there is an direct connection, false otherwise.
	 */
	
	public boolean isInDirectlyConnectedTo(Airport anAirport) {
	    // Delegates the call to the recursive method with a new HashSet for visited airports and depth set to 0.
		return isInDirectlyConnectedTo(anAirport, new HashSet<>(), 0);
	}

	/**
	 * <This method checks if this airport is indirectly connected to another airport within a certain depth limit.>
	 * 
	 * @param <anAirport> The airport to check for indirect connection.
	 * @param <visitedAirports> Set of airports already visited to avoid infinite loops.
     * @param <depth> The current depth of recursion to limit the search depth.
     * @return <true> if there is an indirect connection within the specified depth limit, false otherwise.
     */
	private boolean isInDirectlyConnectedTo(Airport anAirport, Set<Airport> visitedAirports, int depth) {
		if (depth > MAX_DEPTH || visitedAirports.contains(this) || anAirport == null || connectedAirports == null) {
			return false;
		}

		visitedAirports.add(this);

		for (Airport connectedAirport : connectedAirports) {
			if (connectedAirport == anAirport
					|| connectedAirport.isInDirectlyConnectedTo(anAirport, visitedAirports, depth + 1)) {
				return true; // Found a direct or indirect connection
			}
		}

		return false; // No direct or indirect connection found
	}

	/**
	 * <This method prints the common connections of the airport>
	 * 
	 * @param <anAirport> - <an instance of the airports>
	 * @return <commonConnections>
	 */

	public ArrayList<Airport> getCommonConnections(Airport anAirport) {
		ArrayList<Airport> commonConnections = new ArrayList<>();

		for (Airport airport : connectedAirports) {
			if (anAirport.connectedAirports.contains(airport)) {
				commonConnections.add(airport);
			}
		}

		return commonConnections;
	}

	/**
	 * This method prints the names of airlines to the console.
	 * 
	 */
	public void printCompanies() {
		for (String airline : getAirlines()) {
			System.out.println(airline);
		}
	}

}
