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
        JButton jButton1 = new JButton("Find");
        JButton jButton2 = new JButton("Visualize Network");

        add(textField);
        add(jButton1);
        add(jButton2);

        jButton1.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                String cityName = textField.getText();
                Airport airport = centralRegistry.getAirport(cityName);

                if (airport == null) {
                    JOptionPane.showMessageDialog(FindAirportFrame.this, cityName + " does not have an airport ");
                } else {
                    dispose();
                    AirportPageFrame airportPageFrame = new AirportPageFrame(airport);
                    airportPageFrame.setVisible(true);
                }
            }
        });

        jButton2.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                // TODO Auto-generated method stub
            	dispose();
            	Graph11 graph11 = new Graph11();
            	graph11.setVisible(true);
            }
        });

        setVisible(true);
    }

}