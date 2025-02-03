import java.util.Scanner;


public class FirstUniqueCharacter {
    static class Solution {
        public int firstUniqChar(String s) {
            int[] cnt = new int[26];
            int n = s.length();


            for (int i = 0; i < n; ++i) {
                ++cnt[s.charAt(i) - 'a'];
            }

            for (int i = 0; i < n; ++i) {
                if (cnt[s.charAt(i) - 'a'] == 1) {
                    return i;
                }
            }
            return -1; 
        }
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);


        System.out.print("Enter a string: ");
        String input = scanner.nextLine();


        Solution solution = new Solution();
        int result = solution.firstUniqChar(input);


        if (result != -1) {
            System.out.println("The first unique character is at index: " + result);
        } else {
            System.out.println("No unique character found in the string.");
        }


        scanner.close();
    }
}
