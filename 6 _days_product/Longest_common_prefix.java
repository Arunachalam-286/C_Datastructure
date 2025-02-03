import java.util.Scanner;

public class Longest_common_prefix {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of strings: ");
        int n = scanner.nextInt();
        scanner.nextLine(); 
        if (n == 0) {
            System.out.println("The longest common prefix is: ''");
            return;
        }

        String[] strs = new String[n];
        System.out.println("Enter the strings one by one:");
        for (int i = 0; i < n; i++) {
            strs[i] = scanner.nextLine();
        }
        String prefix = strs[0];

        for (int i = 1; i < n; i++) {
            String s = strs[i];
            int j = 0;

            while (j < prefix.length() && j < s.length() && prefix.charAt(j) == s.charAt(j)) {
                j++;
            }

            // Update the prefix to the common part
            prefix = prefix.substring(0, j);

            if (prefix.isEmpty()) {
                break;
            }
        }
        System.out.println("The longest common prefix is: '" + prefix + "'");
        scanner.close();
    }
}
