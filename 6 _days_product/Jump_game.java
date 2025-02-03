import java.util.Scanner;

public class Jump_game {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of elements: ");
        int n = scanner.nextInt();

        System.out.println("Enter the elements of the array:");
        int[] nums = new int[n];
        for (int i = 0; i < n; i++) {
            nums[i] = scanner.nextInt();
        }

        if (nums.length == 0) {
            System.out.println("Yes, you can reach the last index.");
            return;
        }

        int lastPos = n - 1; 
        for (int i = n - 1; i >= 0; i--) {
            
            if (i + nums[i] >= lastPos) {
                lastPos = i; 
            }
        }

        if (lastPos == 0) {
            System.out.println("Yes, you can reach the last index.");
        } else {
            System.out.println("No, you cannot reach the last index.");
        }

        scanner.close();
    }
}
