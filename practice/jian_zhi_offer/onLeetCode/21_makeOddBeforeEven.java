class Solution {
    public int[] exchange(int[] nums) {
        int left = 0, right = nums.length-1;
        while(left < right) {
            while(left <= right && nums[left] % 2 == 1)left++;
            while(left <= right && nums[right] % 2 == 0)right--;
            if(left < right) {
                int tmp = nums[left];
                nums[left] = nums[right];
                nums[right] = tmp;
            }
        }
        return nums;
    }

    public static void main(String[] args) {
        Solution so = new Solution();
        int[] nums = {1,3,5};
        int[] result = so.exchange(nums);
        for(int i =  0;i < result.length;i++) {
            System.out.println(result[i]);
        }
    }
}
