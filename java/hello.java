/* For test OpenJDK Docker file
 *
 * Command Line:
 * $ sudo docker run --rm -v ${PWD}:/srv/ 43bd173514b2 javac tests/java/hello.java
 *
 * 2022-08-23	Rong Tao	Create this
 */
class hello {
	public static void main(String args[]) {
		while (true) {
			System.out.println("Hello.");
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
