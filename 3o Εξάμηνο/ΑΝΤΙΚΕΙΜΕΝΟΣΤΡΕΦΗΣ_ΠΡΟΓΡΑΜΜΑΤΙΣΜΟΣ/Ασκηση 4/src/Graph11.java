import edu.uci.ics.jung.graph.Graph;
import edu.uci.ics.jung.graph.SparseGraph;
import edu.uci.ics.jung.visualization.VisualizationViewer;
import edu.uci.ics.jung.visualization.decorators.ToStringLabeller;
import edu.uci.ics.jung.algorithms.layout.FRLayout;
import edu.uci.ics.jung.algorithms.shortestpath.DijkstraShortestPath;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;



public class Graph11 extends JFrame {
	
	public static int calculateDiameter(Graph<String, String> graph) {
        int diameter = Integer.MIN_VALUE;

        DijkstraShortestPath<String, String> shortestPathAlg = new DijkstraShortestPath<>(graph);

        for (String vertex : graph.getVertices()) {
            for (String targetVertex : graph.getVertices()) {
                if (!vertex.equals(targetVertex)) {
                	int distance = (int) shortestPathAlg.getDistance(vertex, targetVertex).intValue();       
                	if (distance > diameter) {
                        diameter = distance;
                    }
                }
            }
        }

        return diameter;
    }

    public Graph11() {
        setTitle("City Airport Connections Network");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Create a graph
        Graph<String, String> airportGraph = new SparseGraph<>();

        // Add vertices (cities)
        airportGraph.addVertex("Brussels");
        airportGraph.addVertex("Munich");
        airportGraph.addVertex("Thessaloniki");
        airportGraph.addVertex("Athens");
        airportGraph.addVertex("Rome");
        airportGraph.addVertex("Paris");

        // Add edges (flights)
        addEdgeIfNotExists(airportGraph, "Paris", "Rome");
        addEdgeIfNotExists(airportGraph, "Paris", "Munich");
        addEdgeIfNotExists(airportGraph, "Paris", "Brussels");
        addEdgeIfNotExists(airportGraph, "Thessaloniki", "Munich");
        addEdgeIfNotExists(airportGraph, "Athens", "Munich");
        addEdgeIfNotExists(airportGraph, "Thessaloniki", "Munich");
        addEdgeIfNotExists(airportGraph, "Rome", "Munich");
        addEdgeIfNotExists(airportGraph, "Athens", "Thessaloniki");

        // Create a visualization viewer
        VisualizationViewer<String, String> vv = new VisualizationViewer<>(new FRLayout<>(airportGraph));
        vv.setPreferredSize(new Dimension(800, 800)); // Set preferred size

        // Set up vertex labels
        vv.getRenderContext().setVertexLabelTransformer(new ToStringLabeller<>());

        // Set empty edge label transformer to remove text from edges
        vv.getRenderContext().setEdgeLabelTransformer(edge -> "");

        // Create a panel to hold the graph and text field
        JPanel panel = new JPanel();
        panel.setLayout(new BorderLayout());

        // Add the graph to the panel
        panel.add(vv, BorderLayout.CENTER);

        // Diameter calculation
        int diameter = calculateDiameter(airportGraph);

        // Add text field t1 to the panel
        JTextField t1 = new JTextField("Diameter = " + diameter);
        t1.setEditable(false);
        panel.add(t1, BorderLayout.SOUTH);

        // Add the panel to the frame
        getContentPane().add(panel);

        pack();
        setVisible(true); // Make the frame visible
    }

    private void addEdgeIfNotExists(Graph<String, String> graph, String source, String target) {
        if (!graph.containsEdge(source + "-" + target) && !graph.containsEdge(target + "-" + source)) {
            graph.addEdge(source + "-" + target, source, target);
        }
    }

    public static void main(String[] args) {
        new Graph11();
    }
}
