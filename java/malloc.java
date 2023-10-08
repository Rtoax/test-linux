/* For test OpenJDK JVM Stuck file
 *
 * $ jstat -gc $(pidof java)
 * $ jstack -m $(pidof java)
 * $ jstack $(pidof java)
 *
 * 2023-10-07	Rong Tao	Create this.
 */
class Block {
	public int n;
	public int[] i;
	public Block(int n) {
		this.n = n;
	}
	public void init() {
		i = new int[n];
	}
};

class MyThread extends Thread {
	private boolean sleep = true;

	public void setsleep(boolean sleep) {
		this.sleep = sleep;
	}

	@Override
	public void run() {
		long count = 0;
		while (true) {
			count++;
			try {
				System.out.println("malloc. " + count + " in " + this.getId());
				if (sleep) {
					Thread.sleep(1);
				}
				Block b = new Block(1024);
				/* Never delete */
			} catch (Exception e) {
				System.out.println("Got an exception!");
			}
		}
	}
}

class malloc {
	public static void main(String args[]) {
		for (int i = 0; i < 100; i++) {
			MyThread thread = new MyThread();
			thread.setsleep(false);
			thread.start();
		}
	}
}
