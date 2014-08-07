##描述##

两个非递减排序的数组f和g，使得f[i]>g[j]的数对(i, j)共有多少个

##示例##

输入： 两个排序数组f和g

        f = [2, 4, 4, 5, 7, 10]
        g = [3, 3, 4, 6, 9]

输出： 满足f[i]>g[j]的数对(i, j)个数

        16

##代码##

        def compare_two_sorted_array_greater(lst1, lst2):
            lst1 = sorted(lst1)
            lst2 = sorted(lst2)  # mark sure list is sorted
            idx1 = 0
            idx2 = 0
            lst1_len = len(lst1)
            lst2_len = len(lst2)
            count = 0
            while idx1<lst1_len and idx2<lst2_len:
                if lst1[idx1] > lst2[idx2]:
                    count += lst1_len - idx1
                    idx2 += 1
                else:
                    idx1 += 1
            return count

##效率##

&theta;(n)
