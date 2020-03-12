import ListNode from './ListNode';
debugger;

function deleteNode(pListHead: ListNode | null, pToBeDeleted: ListNode | null) {
    if (!pListHead || !pToBeDeleted) {
        return null;
    }
    // not Tail
    if(pToBeDeleted.next != null) {
        let pNext: ListNode = pToBeDeleted.next;
        pToBeDeleted.val = pNext.val;
        pToBeDeleted.next = pNext.next;
    } else if(pListHead === pToBeDeleted) {
        // delete head
        pToBeDeleted = null;
        pListHead = null;
    } else {
        // delete tail
        let pNode: ListNode|null = pListHead;
        while(pNode && pNode.next != pToBeDeleted) {
            pNode = pNode.next;
        }
        pNode && (pNode.next = null);
        pToBeDeleted = null;
    }
    return pListHead;
}

function printList(pListHead: ListNode | null) {
    if(!pListHead) {
        return;
    }
    let pNode: ListNode | null = pListHead;
    let result = '';
    while(pNode != null) {
        result += pNode.val;
        pNode = pNode.next;
    }
    console.log(result);
}

let head: ListNode | null = new ListNode(3);
head.next = new ListNode(2);
head.next.next = new ListNode(4);

printList(head);
head = deleteNode(head, head && head.next);
printList(head);
head = deleteNode(head, head && head.next);
printList(head);
head = deleteNode(head, head);
printList(head);
