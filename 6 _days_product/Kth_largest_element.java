import java.util.Arrays;
import java.util.Scanner;

public class KthLargestSmallestNoFunctions {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of elements in the array: ");
        int n = scanner.nextInt();

        if (n <= 0) {
            System.out.println("Array size must be greater than 0.");
            return;
        }

        int[] arr = new int[n];

        System.out.println("Enter the elements of the array:");
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
        }

        System.out.print("Enter the value of K: ");
        int k = scanner.nextInt();

        if (k <= 0 || k > n) {
            System.out.println("Invalid value of K. It must be between 1 and " + n + ".");
            return;
        }

        Arrays.sort(arr);
        System.out.println("Kth Smallest element: " + arr[k - 1]);
        System.out.println("Kth Largest element: " + arr[n - k]);

        scanner.close();
    }
}
