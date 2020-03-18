class Solution {
    public int[] reversePrint(ListNode head) {
        Stack<ListNode> stack = new Stack<>();
        ListNode tmp = head;
        int count = 0;
        while (tmp != null) {
            stack.push(tmp);
            count++;
            tmp = tmp.next;
        }
        int[] result = new int[count];
        count = 0;
        while(!stack.isEmpty()) {
            ListNode node = stack.pop();
            result[count++] = node.val;
        }
        return result;
    }

    private static class ListNode{
        int val;
        ListNode next;
        ListNode(int x) {
            val = x;
        }
    }
}