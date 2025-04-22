import edu.uci.ics.jung.graph.Graph;
import edu.uci.ics.jung.graph.SparseGraph;
import edu.uci.ics.jung.visualization.VisualizationViewer;
import edu.uci.ics.jung.visualization.decorators.ToStringLabeller;
import edu.uci.ics.jung.algorithms.layout.FRLayout;
import javax.swing.*;

public class Graph {
    public static void main(String[] args) {
        // Create a graph
        Graph<Integer, String> graph = new SparseGraph<>();

        // Add vertices
        graph.addVertex(1);
        graph.addVertex(2);
        graph.addVertex(3);

        // Add edges
        graph.addEdge("Edge1", 1, 2);
        graph.addEdge("Edge2", 2, 3);
        graph.addEdge("Edge3", 3, 1);

        // Create a visualization viewer
        VisualizationViewer<Integer, String> vv = new VisualizationViewer<>(new FRLayout<>(graph));

        // Set up vertex and edge labels
        vv.getRenderContext().setVertexLabelTransformer(new ToStringLabeller<>());
        vv.getRenderContext().setEdgeLabelTransformer(new ToStringLabeller<>());

        // Display the graph
        JFrame frame = new JFrame("Simple Graph Example");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(vv);
        frame.pack();
        frame.setVisible(true);
    }
}

