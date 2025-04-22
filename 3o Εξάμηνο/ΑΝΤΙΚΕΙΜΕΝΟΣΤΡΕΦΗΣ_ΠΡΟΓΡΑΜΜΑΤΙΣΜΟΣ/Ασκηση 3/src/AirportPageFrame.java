import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.security.PublicKey;
import java.util.ArrayList;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.*;
import java.awt.*;

public class AirportPageFrame extends JFrame {

	// private CentralRegistry centralRegistry;
	// private String cityName;

	public AirportPageFrame(Airport airport) {

		// centralRegistry = new CentralRegistry();

		setTitle("Airport Page");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
		setLayout(null);

		// Create a panel for labels
		JPanel panel1 = new JPanel();
		panel1.setBorder(BorderFactory.createLineBorder(Color.black));
		panel1.setLayout(new BorderLayout(50, 50));
		panel1.setBounds(100, 0, 800, 150);

		JTextField t1, t2, t3, t4, t6;
		// String airportName = CentralRegistry.getAirportName(cityName);

		t1 = new JTextField(airport.getName());
		t1.setBounds(120, 60, 150, 30);
		t1.setEditable(false);

		add(t1);

		t2 = new JTextField(airport.getCode());
		t2.setBounds(270, 60, 150, 30);
		t2.setEditable(false);

		add(t2);

		t3 = new JTextField(airport.getCity());
		t3.setBounds(420, 60, 150, 30);
		t3.setEditable(false);

		add(t3);

		t4 = new JTextField(airport.getCountry());
		t4.setBounds(570, 60, 150, 30);
		t4.setEditable(false);
		add(t4);

		// System.out.println("getAirlines:");
		// System.out.println(airport.getAirlines());

		String result = convertArrayListToString(airport.getAirlines());

		JTextArea area = new JTextArea(result);
		area.setBounds(725, 10, 160, 130);
		area.setEditable(false);
		add(area);

		add(panel1);

		setVisible(true);

		// Create the search button
		t6 = new JTextField();
		t6.setBounds(350, 160, 150, 30);
		t6.setEditable(true);
		add(t6);

		JButton findFlightsButton = new JButton("Find flights");
		findFlightsButton.setBounds(500, 155, 120, 40);
		add(findFlightsButton);

		JTextArea area3 = new JTextArea();
		area3.setBounds(50, 210, 450, 200);
		area3.setEditable(false);
		add(area3);

		JTextArea area4 = new JTextArea();
		area4.setBounds(520, 210, 450, 200);
		area4.setEditable(false);
		add(area4);

		findFlightsButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {

				Airport airportΒ = CentralRegistry.getAirport(t6.getText());

				area3.setText(CentralRegistry.getDirectFlightsDetails(airport, airportΒ));

				// wrong output for getInDirectFlightsDetails
				area4.setText(CentralRegistry.getInDirectFlightsDetails(airport, airportΒ));

			}
		}

		);

		// Create the search button

		JButton backToSearchButton = new JButton("Back To Search Screen");
		add(backToSearchButton);
		backToSearchButton.setBounds(400, 430, 200, 40);

		backToSearchButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				dispose();
				FindAirportFrame findAirportFrame = new FindAirportFrame();

				findAirportFrame.setVisible(true);
			}
		});

		setSize(1000, 600);

	}

	public static String convertArrayListToString(ArrayList<String> arrayList) {
		StringBuilder resultStringBuilder = new StringBuilder();

		// Iterate through the ArrayList
		for (String str : arrayList) {
			// Append the line to the result with a newline character
			resultStringBuilder.append(str);
			resultStringBuilder.append(System.lineSeparator());
		}

		// Convert StringBuilder to String
		return resultStringBuilder.toString();
	}

}
