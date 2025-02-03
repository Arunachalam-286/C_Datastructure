import java.util.Scanner;
import java.util.Stack;


public class Postfix_expression_evaluation {


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);


        System.out.print("Enter a postfix expression: ");
        String postfix = scanner.nextLine();


        int result = evaluatePostfix(postfix);


        System.out.println("The postfix evaluation is: " + result);
       
        scanner.close();
    }


    public static int evaluatePostfix(String postfix) {
        Stack<Integer> stack = new Stack<>();
        int a, b, result;


        for (int i = 0; i < postfix.length(); i++) {
            char ch = postfix.charAt(i);


            if (Character.isDigit(ch)) {
                stack.push(ch - '0');
            }
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
                b = stack.pop();
                a = stack.pop();
                switch (ch) {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;
                    case '/': result = a / b; break;
                    case '%': result = a % b; break;
                    default: throw new IllegalArgumentException("Invalid operator: " + ch);
                }
                stack.push(result);
            }
        }

        return stack.pop();
    }
}
