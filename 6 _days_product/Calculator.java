import java.util.*;


public class Calculator {
    public int calculate(String s) {
        Deque<Integer> stack = new ArrayDeque<>();
        int sign = 1; 
        int ans = 0;
        int n = s.length();


        for (int i = 0; i < n; ++i) {
            char c = s.charAt(i);


            if (Character.isDigit(c)) {
                
                int num = 0;
                while (i < n && Character.isDigit(s.charAt(i))) {
                    num = num * 10 + (s.charAt(i) - '0');
                    i++;
                }
                i--; 
                ans += sign * num;
            } else if (c == '+') {
                sign = 1;
            } else if (c == '-') {
                sign = -1;
            } else if (c == '(') {
                stack.push(ans);
                stack.push(sign);
                ans = 0;
                sign = 1;
            } else if (c == ')') {
                ans = stack.pop() * ans + stack.pop();
            }
        }


        return ans;
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Calculator calculator = new Calculator();


        System.out.print("Enter a mathematical expression: ");
        String expression = scanner.nextLine();


        expression = expression.replaceAll("\\s+", "");


        try {
            int result = calculator.calculate(expression);
            System.out.println("Result: " + result);
        } catch (Exception e) {
            System.out.println("Invalid expression! Please check your input.");
        }


        scanner.close();
    }
}
