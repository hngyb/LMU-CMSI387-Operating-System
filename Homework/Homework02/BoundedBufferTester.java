public class BoundedBufferTester {
  public static void main(String[] args) {
    BoundedBuffer test = new BoundedBuffer();
    int testValue = (int)(Math.random()*50);
    Thread t1 = new Thread(new Runnable() {
      public void run() {
        try {
            test.insert(testValue);
            System.out.println("Value inserted is "+ testValue);
          } catch (InterruptedException e) {
            System.out.println("Error when attempting to insert value");
          }
        }
      }); 

      Thread t2 = new Thread(new Runnable() {
       public void run() {
        try {
            String valueMatches = "isn't correct.";
            int retrievedValue = (int)test.retrieve();
            if(retrievedValue == testValue){
              valueMatches = "is correct";
            }
            System.out.println("Value retrieved is "+retrievedValue +" which "+valueMatches);
          } catch (InterruptedException e) {
            System.out.println("Error when attempting to retrieve value");
          }
        }
      }); 

    
    System.out.println("Running:");
    t1.start();
    try {
      t1.join();
    } catch (InterruptedException e) {
      System.out.println("Error when attempting to join t1");
    }
    t2.start();
    try {
      t2.join();
    } catch (InterruptedException e) {
      System.out.println("Error when attempting to join t2");
    } 
  }
}
