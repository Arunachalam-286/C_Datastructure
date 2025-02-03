import java.util.Scanner;

public class Longest_palindromic_substring{
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a string: ");
        String str = scanner.nextLine();

        int maxLength = 1; 
        int start = 0;     
        int len = str.length();

        for (int i = 0; i < len; i++) {
            for (int j = i; j < len; j++) {
                boolean isPalindrome = true;

                for (int k = 0; k < (j - i + 1) / 2; k++) {
                    if (str.charAt(i + k) != str.charAt(j - k)) {
                        isPalindrome = false;
                        break;
                    }
                }

                if (isPalindrome && (j - i + 1) > maxLength) {
                    start = i;
                    maxLength = j - i + 1;
                }
            }
        }

        System.out.println("Longest Palindromic Substring: " + str.substring(start, start + maxLength));

        scanner.close();
    }
}
