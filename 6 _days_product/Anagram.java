import java.util.Scanner;

public class Anagram {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the first string: ");
        String s = scanner.nextLine().toLowerCase();

        System.out.print("Enter the second string: ");
        String t = scanner.nextLine().toLowerCase();

        if (s.length() != t.length()) {
            System.out.println("The strings are not anagrams.");
            return;
        }

        int[] cnt = new int[26];

        for (int i = 0; i < s.length(); ++i) {
            cnt[s.charAt(i) - 'a']++;
            cnt[t.charAt(i) - 'a']--;
        }

        boolean isAnagram = true;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] != 0) {
                isAnagram = false;
                break;
            }
        }

        if (isAnagram) {
            System.out.println("The strings are anagrams.");
        } else {
            System.out.println("The strings are not anagrams.");
        }

        scanner.close();
    }
}
