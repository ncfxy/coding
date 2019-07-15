/**
 * Definition for singly-linked list.
 * function ListNode(val) {
 *     this.val = val;
 *     this.next = null;
 * }
 */

function ListNode(val) {
    this.val = val;
    this.next = null;
}

/**
 * @param {ListNode} l1
 * @param {ListNode} l2
 * @return {ListNode}
 */
var addTwoNumbers = function (l1, l2) {
    var ans = l1, father1 = l1, father2 = l2;
    var extra = 0;
    while (l1 != null && l2 != null) {
        l1.val = l1.val + l2.val + extra;
        extra = Math.floor(l1.val / 10);
        l1.val = l1.val % 10;
        father1 = l1;
        father2 = l2;
        l1 = l1.next;
        l2 = l2.next;
        delete father2;
    }
    if(l1 == null){
        father1.next = l2;
        l1 = l2;
    }

    while(l1 != null){
        l1.val = l1.val + extra;
        extra = Math.floor(l1.val / 10);
        l1.val = l1.val % 10;
        father1 = l1;
        l1 = l1.next;
    }
    if(extra > 0) {
        var newNode = new ListNode(extra);
        father1.next = newNode;
    }
    return ans;
};

function test() {
    function outputListNode(list){
        var result = '';
        while(list != null){
            result += list.val;
            list = list.next;
        }
        console.log(result);
    };
    
    var l1 = new ListNode(8);
    l1.next = new ListNode(3);
    
    var l2 = new ListNode(2);
    l2.next = new ListNode(6);
    
    outputListNode(l1);
    outputListNode(l2);
    outputListNode(addTwoNumbers(l1, l2));
}

test();
