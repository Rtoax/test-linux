/* For test OpenJDK Docker file
 *
 * Command Line:
 * $ sudo docker run --rm -v ${PWD}:/srv/ 43bd173514b2 javac tests/java/hello.java
 *
 * 2022-08-23	Rong Tao	Create this
 */
class hello {
	public static void main(String args[]) {
		System.out.println("Hello.");
	}
}
