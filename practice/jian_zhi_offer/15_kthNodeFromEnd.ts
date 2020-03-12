import ListNode from './ListNode';

function findKthToTailListNode(pListHead: ListNode| null, k: number) {
    if(pListHead == null || k <= 0 || Math.floor(k) !== k) {
        return null;
    }
    let pHead = pListHead;
    let pBehind: ListNode | null = pListHead;
    for(let i = 0;i < k - 1; i++) {
        if(pHead && pHead.next != null) {
            pHead = pHead.next
        } else {
            return null;
        }
    }
    while(pHead.next != null) {
        pHead && (pHead = pHead.next);
        pBehind && (pBehind = pBehind.next);
    }
    return pBehind;
}

let listHead = new ListNode(1);
listHead.next = new ListNode(2);
listHead.next.next = new ListNode(3);
listHead.next.next.next = new ListNode(4);

console.log(findKthToTailListNode(listHead, 1)?.val);
console.log(findKthToTailListNode(listHead, 2)?.val);
console.log(findKthToTailListNode(listHead, 3)?.val);
console.log(findKthToTailListNode(listHead, 4)?.val);
