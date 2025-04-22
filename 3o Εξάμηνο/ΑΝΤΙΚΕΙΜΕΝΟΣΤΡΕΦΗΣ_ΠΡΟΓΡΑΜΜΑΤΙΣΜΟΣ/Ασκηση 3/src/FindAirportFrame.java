
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import java.awt.*;

public class FindAirportFrame extends JFrame {

	private CentralRegistry centralRegistry;

	public FindAirportFrame() {

		setTitle("Find Airport");
		setSize(300, 150);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);

		setLayout(new FlowLayout());

		TextField textField = new TextField(20);
		JButton jButton = new JButton("Find");

		add(textField);
		add(jButton);

		jButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				String cityName = textField.getText();
				Airport airport = CentralRegistry.getAirport(cityName);

				if (airport == null) {
					JOptionPane.showMessageDialog(FindAirportFrame.this, cityName + " does not have an airport ");
				} else {
					dispose();
					AirportPageFrame airportPageFrame = new AirportPageFrame(airport);
					airportPageFrame.setVisible(true);
				}
			}

		});

		setVisible(true);
	}

}
