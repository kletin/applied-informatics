
public class Flight {
	
private Airport airportA;
private Airport airportB;
private int durationMinutes;
private String airline;
public String source;
public String destination;

public Flight(Airport airportA, Airport airportB, int durationMinutes, String airline) {
	this.airportA = airportA;
	this.airportB = airportB;
	this.durationMinutes = durationMinutes;
	this.airline = airline;
	
/**
 * <This method returns the airport A .>
 * 		 
 * @return <airportA> the name of the airport.
 */

}

public Airport getAirportA() {
	return airportA;
}

/**
 * <This method returns the airport B .>
 * 		 
 * @return <airportB> the name of the airport.
 */

public Airport getAirportB() {
	return airportB;
}

/**
 * <This method returns the airline that is connected with the flight.>
 * 		 
 * @return <airline> the name of the company.
 */

public String getAirline() {
	return airline;
}

/**
 * <This method returns the duration of the flight.>
 * 		 
 * @return <durationMinutes> the duration of the flight.
 */

public int getDurationMinutes() {
	return durationMinutes;
}

@Override

public String toString() {
	return  "Flight operated by " +airline+ ", duration" +durationMinutes+ "minutes";
}

}



