class blocked {
	public static void main(String[] args) throws Exception {
		Object lock = new Object();
		Thread[] threads = new Thread[10];
		for (int i = 0; i < threads.length; i++) {
			threads[i] = new Thread(() -> {
				synchronized (lock) {
					try {
						Thread.sleep(1000000);
					} catch (InterruptedException e) {
						throw new RuntimeException(e);
					}
				}
			});
			threads[i].start();
		}

		for (Thread thread : threads) {
			thread.join();
		}
	}
}
