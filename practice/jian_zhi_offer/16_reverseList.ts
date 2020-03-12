import ListNode from './ListNode';
import {printLinkedList} from './ListNode';

debugger;

function reverseList(listNode: ListNode | null) {
    if(listNode == null ) {
        return null;
    }
    if(listNode.next == null) {
        return listNode;
    }
    let newHead: ListNode | null = null;
    let prev: ListNode | null = null;
    let node: ListNode | null = listNode;
    while(node != null) {
        let next: ListNode | null = node.next;
        if(next == null) {
            newHead = node;
        }
        node.next = prev;
        prev = node;
        node = next;
    }
    return newHead;
}

let head: ListNode | null = new ListNode(1);
head.next = new ListNode(2);
head.next.next = new ListNode(3);
head.next.next.next = new ListNode(4);
printLinkedList(head);
head = reverseList(head);
printLinkedList(head);


