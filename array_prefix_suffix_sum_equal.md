##描述##

对于一个长度为n的**未排序**数组f，使得f[0]+f[1]+...+f[i]=f[j]+...+f[n-1]的数对(i, j)共有多少

##示例##

输入： 一个未排序的数组

        f = [4, 3, 3, 4]

输出： `4`

##代码##

        def array_prefix_suffix_sum_equal(lst):
            count = 0
            head_idx = 0
            tail_idx = len(lst) - 1
            
            prefix_sum = 0
            suffix_sum = 0
            
            while head_idx < len(lst) or tail_idx > -1:
                prefix_sum += lst[head_idx]
                suffix_sum += lst[tail_idx]
                if prefix_sum > suffix_sum:
                    prefix_sum -= lst[head_idx]
                    tail_idx -= 1
                elif prefix_sum < suffix_sum:
                    suffix_sum -= lst[tail_idx]
                    head_idx += 1            
                else:
                    count += 1
                    head_idx += 1
                    tail_idx -= 1
            return count
