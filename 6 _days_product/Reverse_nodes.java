import java.util.Scanner;


class ListNode {
    int val;
    ListNode next;
    ListNode() {}
    ListNode(int val) { this.val = val; }
    ListNode(int val, ListNode next) { this.val = val; this.next = next; }
}


public class Reverse_nodes {
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode dummy = new ListNode(0, head);
        ListNode pre = dummy;


        while (pre != null) {
            ListNode cur = pre;
            for (int i = 0; i < k; i++) {
                cur = cur.next;
                if (cur == null) {
                    return dummy.next;
                }
            }


            ListNode node = pre.next;
            ListNode nxt = cur.next;
            cur.next = null;
            pre.next = reverse(node);
            node.next = nxt;
            pre = node;
        }


        return dummy.next;
    }
    private ListNode reverse(ListNode head) {
        ListNode dummy = new ListNode();
        ListNode cur = head;
        while (cur != null) {
            ListNode nxt = cur.next;
            cur.next = dummy.next;
            dummy.next = cur;
            cur = nxt;
        }
        return dummy.next;
    }
    private ListNode createList(int[] arr) {
        ListNode dummy = new ListNode(0);
        ListNode cur = dummy;
        for (int num : arr) {
            cur.next = new ListNode(num);
            cur = cur.next;
        }
        return dummy.next;
    }
    private void printList(ListNode head) {
        ListNode temp = head;
        while (temp != null) {
            System.out.print(temp.val + " ");
            temp = temp.next;
        }
        System.out.println();
    }


    public static void main(String[] args) {
        ReverseNodesInKGroup solution = new ReverseNodesInKGroup();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the size of the linked list: ");
        int n = scanner.nextInt();
        System.out.print("Enter the elements of the linked list: ");
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
        }
        System.out.print("Enter the value of k: ");
        int k = scanner.nextInt();
        ListNode head = solution.createList(arr);
        System.out.println("Original Linked List:");
        solution.printList(head);
        ListNode result = solution.reverseKGroup(head, k);
        System.out.println("Reversed Linked List in k-Groups:");
        solution.printList(result);


        scanner.close();
    }
}
