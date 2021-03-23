class Solution extends Thread{
    public ListNode reverseList(ListNode head) {
        ListNode current = head, before = null;
        while(current != null) {
            ListNode tmpNext = current.next;
            current.next = before;
            before = current;
            current = tmpNext;
        }
        return before;
    }

    public void run() {
        ListNode node  = new ListNode(1);
        node.next = new ListNode(2);
        node.next.next = new ListNode(3);
        ListNode result = this.reverseList(node);
        ListNode.printList(result);
    }

    public static void main(String[] args) {
        new Solution().start();
    }
}