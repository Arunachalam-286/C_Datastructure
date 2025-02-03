import java.util.Scanner;


public class Valid_parentheses {


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
       
        System.out.print("Enter a parentheses string: ");
        String input = scanner.nextLine();
       
        Solution solution = new Solution();
       
        int result = solution.longestValidParentheses(input);
        System.out.println("Length of the longest valid parentheses substring: " + result);
       
        scanner.close();
    }
}


class Solution {
    public int longestValidParentheses(String s) {
        int n = s.length();  
        int[] f = new int[n + 1];  
        int ans = 0; 


        for (int i = 2; i <= n; ++i) {  
            if (s.charAt(i - 1) == ')') {  
                if (s.charAt(i - 2) == '(') {  
                    f[i] = f[i - 2] + 2;  
                } else {  
                    int j = i - f[i - 1] - 1;
                    if (j > 0 && s.charAt(j - 1) == '(') {
                        f[i] = f[i - 1] + 2 + f[j - 1];
                    }
                }
                ans = Math.max(ans, f[i]); 
            }
        }
        return ans;  longest valid parentheses substring
    }
}
