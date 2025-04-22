 public class Car extends Vehicle {
     private int numberOfDoors;

     public Car(String name, int numberOfDoors) {
         super(name);
         this.numberOfDoors = numberOfDoors;
     }
      public static void printStart(){
          System.out.println("The car is starting.Buckle up");
         }
     }
