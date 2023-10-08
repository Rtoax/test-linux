class swap {
	/* byteorder swap */
	public static native void swapFloatFile(String in, String out);
}

class Main {
	public static void main(String[] args)throws java.io.IOException {
		System.loadLibrary("swap");
		swap.swapFloatFile("/etc/os-release", "os-release");
	}
}
