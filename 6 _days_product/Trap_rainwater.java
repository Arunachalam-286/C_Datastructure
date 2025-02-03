import java.util.Scanner;

public class Trap_rainwater {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of bars: ");
        int n = scanner.nextInt();

        if (n == 0) {
            System.out.println("The amount of trapped rainwater is: 0");
            return;
        }

        System.out.print("Enter the heights of the bars: ");
        int[] height = new int[n];
        for (int i = 0; i < n; i++) {
            height[i] = scanner.nextInt();
        }

        int[] left = new int[n];
        int[] right = new int[n];

        left[0] = height[0];
        right[n - 1] = height[n - 1];

        for (int i = 1; i < n; ++i) {
            left[i] = Math.max(left[i - 1], height[i]);
        }

        for (int i = n - 2; i >= 0; --i) {
            right[i] = Math.max(right[i + 1], height[i]);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += Math.min(left[i], right[i]) - height[i];
        }

        System.out.println("The amount of trapped rainwater is: " + ans);

        scanner.close();
    }
}
