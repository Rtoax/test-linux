class poll {
	public static native int init();
	public static native int poll(int timeout);
	public static native int echo(int clientfd);
};

class swap {
	/* byteorder swap */
	public static native void swapFloatFile(String in, String out);
}

class Main {
	public static void main(String[] args)throws java.io.IOException {
		System.loadLibrary("swap");
		swap.swapFloatFile("/etc/os-release", "os-release");

		System.loadLibrary("poll");
		poll.init();

		while (true) {
			poll.echo(poll.poll(-1));
		}
	}
}
