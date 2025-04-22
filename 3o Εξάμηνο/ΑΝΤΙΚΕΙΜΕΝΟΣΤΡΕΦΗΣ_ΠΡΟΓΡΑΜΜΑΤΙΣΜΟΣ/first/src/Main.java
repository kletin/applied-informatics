public class Main {
    public static void main(String[] args) {
        System.out.println("Hello, Java World!");

        // Δημιουργία αντικειμένων από τις κλάσεις
        VariablesDemo variablesDemo = new VariablesDemo();
        variablesDemo.displayVariables();

        ControlFlowDemo controlFlowDemo = new ControlFlowDemo();
        controlFlowDemo.checkNumber(10);

        LoopsDemo loopsDemo = new LoopsDemo();
        loopsDemo.runLoops();

        MethodsDemo methodsDemo = new MethodsDemo();
        int sum = methodsDemo.add(5, 7);
        System.out.println("Άθροισμα: " + sum);

        Car myCar = new Car("Toyota");
        myCar.displayModel();

        Dog myDog = new Dog();
        myDog.makeSound();
        myDog.bark();
    }
}