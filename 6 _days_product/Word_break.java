import java.util.*;

public class Word_break {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the string: ");
        String s = scanner.nextLine();

        System.out.print("Enter the number of words in the dictionary: ");
        int n = scanner.nextInt();
        scanner.nextLine(); 
        System.out.println("Enter the dictionary words:");
        Set<String> wordDictSet = new HashSet<>();
        for (int i = 0; i < n; i++) {
            wordDictSet.add(scanner.nextLine());
        }

        boolean[] dp = new boolean[s.length() + 1];
        dp[0] = true; 
        for (int i = 1; i <= s.length(); i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && wordDictSet.contains(s.substring(j, i))) {
                    dp[i] = true; 
                    break; 
                }
            }
        }

        if (dp[s.length()]) {
            System.out.println("The string can be segmented into words from the dictionary.");
        } else {
            System.out.println("The string cannot be segmented into words from the dictionary.");
        }

        scanner.close();
    }
}
