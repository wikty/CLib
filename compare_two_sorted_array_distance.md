##描述##

两个非递减排序数组f和g，求|f[i]-g[j]|的最小值

##示例##

输入：两个排序数组f和g

        f = [2, 13, 25, 77]
        g = [9, 18, 24, 60]

输出： abs(f[i]-g[j])的最小值

        1  # f[2]-g[2]为最小值

##代码##

        def compare_two_sorted_array_distance(lst1, lst2):
            lst1 = sorted(lst1)
            lst2 = sorted(lst2)  # mark sure list is sorted
            idx1 = 0
            idx2 = 0
            lst1_len = len(lst1)
            lst2_len = len(lst2)
            min_distance = max(lst1+lst2) + 1
            while idx1<lst1_len and idx2<lst2_len:
                distance = abs(lst1[idx1]-lst2[idx2])
                if distance < min_distance:
                    min_distance = distance
                if lst1[idx1] > lst2[idx2]:
                    idx2 += 1
                elif lst1[idx1] < lst2[idx2]:
                    idx1 += 1
                else:
                    return 0
            return min_distance
