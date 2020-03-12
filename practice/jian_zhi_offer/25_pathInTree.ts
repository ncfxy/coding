import { BinaryTreeNode } from "./TreeNode";


function findPath(root: BinaryTreeNode| null, expectedSum: number) {
    if(root == null) {
        return;
    }
    const path: number[] = [];
    findPathRecursive(root, expectedSum, path, 0);
}

function findPathRecursive(root: BinaryTreeNode | null, expectedSum: number, path: number[], currentSum: number) {
    if(root == null) {
        return;
    }
    path.push(root.val);
    if(currentSum + root.val === expectedSum) {
        console.log(path);
    }
    if(root.left) {
        findPathRecursive(root.left, expectedSum, path, currentSum + root.val);
    }
    if(root.right) {
        findPathRecursive(root.right, expectedSum, path, currentSum + root.val);
    }
    path.pop();
}

const root: BinaryTreeNode = new BinaryTreeNode(10);
root.left = new BinaryTreeNode(5);
root.right = new BinaryTreeNode(12);
root.left.left = new BinaryTreeNode(4);
root.left.right = new BinaryTreeNode(7);
console.log('Test Case 1: ');
findPath(root, 22);
console.log('Test Case 2: ');
findPath(root, 19);

