class swap {
	/* byteorder swap */
	public static native void swap_float(String in, String out);
}

class Main {
	public static void main(String[] args)throws java.io.IOException {
		System.loadLibrary("swap");
		swap.swap_float("/etc/os-release", "os-release");
	}
}
