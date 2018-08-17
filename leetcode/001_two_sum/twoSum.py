class Solution:
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        ans = []
        myMap = {}
        for i in range(len(nums)):
            if nums[i] in myMap:
                myMap[nums[i]].append(i)
            else:
                myMap[nums[i]] = [i]
        
        for key in myMap:
            temp = target - key
            if temp in myMap:
                ans.append(myMap[key][0])
                if(temp == key):
                    ans.append(myMap[key][1])
                else:
                    ans.append(myMap[temp][0])
                break
        ans.sort()
        return ans

so = Solution()
nums = [2, 7, 11, 15]
target = 9
print(so.twoSum(nums, target))
