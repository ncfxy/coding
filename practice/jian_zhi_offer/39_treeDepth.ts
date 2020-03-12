import { BinaryTreeNode } from "./TreeNode";


function treeDepth(root: BinaryTreeNode | null): number {
    if(root == null) {
        return 0;
    }
    let leftDepth = treeDepth(root.left);
    let rightDepth = treeDepth(root.right);
    return leftDepth > rightDepth ? leftDepth + 1: rightDepth + 1;
}


function isBalance(root: BinaryTreeNode | null): [boolean, number] {
    if(root == null) {
        return [true, 0];
    }
    let [leftIsBalance, leftDepth] = isBalance(root.left);
    let [rightIsBalance, rightDepth] = isBalance(root.right);
    if(leftIsBalance && rightIsBalance) {
        let diff = leftDepth - rightDepth;
        if(diff >= -1 && diff <= 1) {
            let depth = leftDepth > rightDepth ? leftDepth + 1: rightDepth + 1;
            return [true, depth];
        }
    }
    return [false, 0];
}

let root: BinaryTreeNode = new BinaryTreeNode(1);
root.left = new BinaryTreeNode(2);
root.right = new BinaryTreeNode(3);
root.left.left = new BinaryTreeNode(4);
root.left.right = new BinaryTreeNode(5);
console.log(treeDepth(root));
console.log(isBalance(root));
root.left.left.left = new BinaryTreeNode(6);
console.log(treeDepth(root));
console.log(isBalance(root));

