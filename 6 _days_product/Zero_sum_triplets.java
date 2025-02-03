import java.util.Arrays;
import java.util.Scanner;

public class Zero_sum_triplets
{
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of elements in the array: ");
        int n = scanner.nextInt();

        if (n < 3) {
            System.out.println("Array must have at least 3 elements to form a triplet.");
            return;
        }

        int[] arr = new int[n];

        System.out.println("Enter the elements of the array:");
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
        }

        
        Arrays.sort(arr);
        int count = 0;

        
        for (int i = 0; i < n - 2; i++) {
            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = arr[i] + arr[left] + arr[right];

                if (sum == 0) {
                    System.out.println("Triplet found: (" + arr[i] + ", " + arr[left] + ", " + arr[right] + ")");
                    count++;
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++; 
                } else {
                    right--; 
                }
            }
        }

        if (count == 0) {
            System.out.println("No zero-sum triplets found.");
        }

        System.out.println("Count of zero-sum triplets: " + count);
        scanner.close();
    }
}
