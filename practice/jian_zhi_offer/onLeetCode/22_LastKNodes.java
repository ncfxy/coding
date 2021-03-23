class Solution extends Thread{
    public ListNode getKthFromEnd(ListNode head, int k) {
        ListNode p1 = head, p2 = head;
        for(int i = 0;i < k && p1 != null;i++) {
            p1 = p1.next;
        }
        while(p1 != null) {
            p1 = p1.next;
            p2 = p2.next;
        }
        return p2;
    }

    public void run() {
        ListNode node  = new ListNode(1);
        node.next = new ListNode(2);
        node.next.next = new ListNode(3);
        node.next.next.next  = new ListNode(4);
        node.next.next.next.next = new ListNode(5);
        ListNode returned = this.getKthFromEnd(node, 2);
        ListNode.printList(returned);
    }

    public static void main(String[] args) {
        new Solution().start();
    }
}