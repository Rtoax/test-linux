/**
 * Merge Sort
 * https://github.com/CyC2018/Interview-Notebook/
 */
public class MergeSort {

	private int[] aux;

	/**
	 * Merge
	 */
	private void merge(int[] a, int lo, int mid, int hi)
	{
		int i = lo, j = mid + 1;

		for (int k = lo; k <= hi; k++)
		{
			aux[k] = a[k]; // copy data to tmp array
		}

		for (int k = lo; k <= hi; k++)
		{
			if (i > mid) a[k] = aux[j++];
			else if (j > hi) a[k] = aux[i++];
			else if (aux[i]<=a[j]) a[k] = aux[i++]; // for stable
			else a[k] = aux[j++];
		}
	}
	/**
	 * Top-down merge sort
	 */
	public void tdsort(int[] a)
	{
		aux = new int[a.length];
		tdsort(a, 0, a.length - 1);
	}

	private void tdsort(int[] a, int lo, int hi)
	{
		aux = new int[a.length];
		if (hi <= lo) return;
		int mid = lo + (hi - lo) / 2;
		tdsort(a, lo, mid);
		tdsort(a, mid + 1, hi);
		merge(a, lo, mid, hi);
	}
	/**
	 * Bottom up merge sort
	 */
	public void busort(int[] a)
	{
		int N = a.length;
		aux = new int[N];
		for (int sz = 1; sz < N; sz += sz)
		{
			for (int lo = 0; lo < N - sz; lo += sz + sz)
			{
				merge(a, lo, lo + sz - 1, Math.min(lo + sz + sz - 1, N - 1));
			}
		}
	}
	public void show(int[] a)
	{
		int N = a.length;
		for(int i=0;i<N;i++)
		{
			System.out.print(a[i]+" ");
		}
		System.out.println();
	}
	static public void main(String[]args)
	{
		int a[] = {5,4,3,2,1};
		MergeSort ms = new MergeSort();
		ms.show(a);
		ms.tdsort(a);
		ms.show(a);
	}
}
