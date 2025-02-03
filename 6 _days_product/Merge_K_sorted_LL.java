import java.util.Scanner;
class Node {
   int data;        
   Node next;
   Node(int data) {
       this.data = data;
       this.next = null;
   }
}
public class Merge_K_sorted_LL{
   public static Node mergeTwoLists(Node l1, Node l2) {
       if (l1 == null) return l2;
       if (l2 == null) return l1;
       Node result;
       if (l1.data < l2.data) {
           result = l1;
           result.next = mergeTwoLists(l1.next, l2);
       } else {
           result = l2;
           result.next = mergeTwoLists(l1, l2.next);
       }
       return result;
   }
   public static Node mergeKLists(Node[] lists, int k) {
       if (k == 0) return null;
       if (k == 1) return lists[0];
       
       int mid = k / 2;
       for (int i = 0; i < mid; i++) {
           lists[i] = mergeTwoLists(lists[i], lists[k - i - 1]);
       }
       return mergeKLists(lists, (k + 1) / 2);
   }
   
   public static void display(Node head) {
       if (head == null) {
           System.out.println("The list is empty.");
           return;
       }
       Node temp = head;
       while (temp != null) {
           System.out.print(temp.data + " -> ");
           temp = temp.next;
       }
       System.out.println("NULL");
   }
   public static void main(String[] args) {
       Scanner scanner = new Scanner(System.in);
       System.out.print("Enter the number of sorted linked lists (k): ");
       int k = scanner.nextInt();
       Node[] lists = new Node[k];
       for (int i = 0; i < k; i++) {
           System.out.print("Enter the number of nodes in list " + (i + 1) + ": ");
           int n = scanner.nextInt();
           Node head = null, tail = null;
           for (int j = 0; j < n; j++) {
               System.out.print("Enter data for node " + (j + 1) + " in list " + (i + 1) + ": ");
               int value = scanner.nextInt();
               Node newNode = new Node(value);
               if (head == null) {
                   head = newNode;
                   tail = newNode;
               } else {
                   tail.next = newNode;
                   tail = newNode;
               }
           }
           lists[i] = head;
       }
       Node mergedList = mergeKLists(lists, k);
       System.out.print("The merged sorted linked list is: ");
       display(mergedList);
       scanner.close();
   }
}
